/*
 * Mesa 3-D graphics library
 * Version:  5.0
 *
 * Copyright (C) 1999-2003  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* $Id: miniglx_events.c,v 1.1.2.2 2003/04/17 15:46:42 keithw Exp $ */


/**
 * \file miniglx_events.c
 * \brief Mini GLX client/server communication functions.
 * \author Keith Whitwell
 *
 * The Mini GLX interface is a subset of the GLX interface, plus a
 * minimal set of Xlib functions.  This file adds interfaces to
 * arbitrate a single cliprect between multiple direct rendering
 * clients.
 *
 * A fairly complete client/server non-blocking communication
 * mechanism.  Probably overkill given that none of our messages
 * currently exceed 1 byte in length and take place over the
 * relatively benign channel provided by a unix domain socket.
 */

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <linux/kd.h>
#include <linux/vt.h>

#include "miniglxP.h"

#include "glapi.h"

#define MINIGLX_FIFO_NAME "/tmp/miniglx.fifo"


enum msgs {
   _CanIHaveFocus,
   _IDontWantFocus,
   _YouveGotFocus,
   _YouveLostFocus,
   _RepaintPlease,
};


static XEvent *queue_event( Display *dpy )
{
   int incr = (dpy->eventqueue.tail + 1) & MINIGLX_EVENT_QUEUE_MASK;
   if (incr == dpy->eventqueue.head)
      return 0;
   else {
      dpy->eventqueue.tail = incr;
      return &dpy->eventqueue.queue[incr];
   }
}

static int dequeue_event( Display *dpy, XEvent *ev )
{
   if (dpy->eventqueue.tail == dpy->eventqueue.head)
      return False;
   else {
      ev = &dpy->eventqueue.queue[dpy->eventqueue.head];
      dpy->eventqueue.head += 1;
      dpy->eventqueue.head &= MINIGLX_EVENT_QUEUE_MASK;
      return True;
   }
}


static void shut_fd( Display *dpy, int i )
{
   XEvent *er;

   if (dpy->fd[i].fd < 0) 
      return;

   if (i == 0) {
      fprintf(stderr, "server connection lost\n");
      exit(1);
   }

   shutdown (dpy->fd[i].fd, SHUT_RDWR);
   close (dpy->fd[i].fd);
   dpy->fd[i].fd = -1;
   dpy->fd[i].readbuf_count = 0;
   dpy->fd[i].writebuf_count = 0;

   /* Pass this to the application as a DestroyNotify event.
    */
   er = queue_event(dpy);
   if (!er) return;
   er->xdestroywindow.type = DestroyNotify;
   er->xdestroywindow.serial = 0;
   er->xdestroywindow.send_event = 0;
   er->xdestroywindow.display = dpy;
   er->xdestroywindow.window = (Window)i;	
}

static int send_msg( Display *dpy, int i,
		     const void *msg, size_t sz )
{
   int cnt = dpy->fd[i].writebuf_count;
   if (MINIGLX_BUF_SIZE - cnt < sz) {
      fprintf(stderr, "client %d: writebuf overflow\n", i);
      return False;
   }
   
   memcpy( dpy->fd[i].writebuf + cnt, msg, sz ); cnt += sz;
   dpy->fd[i].writebuf_count = cnt;
   return True;
}

static int send_char_msg( Display *dpy, int i, char msg )
{
   return send_msg( dpy, i, &msg, sizeof(char));
}

static int blocking_read( Display *dpy, int connection, 
			  char *msg, size_t msg_size )
{
   int i, r;

   for (i = 0 ; i < msg_size ; i += r) {
      r = read(dpy->fd[connection].fd, msg + i, msg_size - i);
      if (r < 1) {
	 shut_fd(dpy,connection);
	 return False;
      }
   }

   return True;
}



static int welcome_message_part( Display *dpy, int i, void **msg, int sz )
{
   if (dpy->IsClient) {
      int sz;
      if (!blocking_read( dpy, i, (char *)&sz, sizeof(sz))) return False;
      if (!*msg) *msg = malloc(sz);
      if (!*msg) return False;
      if (!blocking_read( dpy, i, *msg, sz )) return False;
   }
   else {
      if (!send_msg( dpy, i, &sz, sizeof(sz))) return False;
      if (!send_msg( dpy, i, *msg, sz )) return False;
   }

   return True;
}

static int welcome_message( Display *dpy, int i )
{
   void *tmp = &dpy->shared;

   if (!welcome_message_part( dpy, i, &tmp, sizeof(dpy->shared)))
      return False;
      
   if (!welcome_message_part( dpy, i, (void **)&dpy->driverClientMsg, 
			      dpy->driverClientMsgSize ))
      return False;

   return True;
}



static int handle_new_client( Display *dpy )
{
   struct sockaddr_un client_address;
   unsigned int l = sizeof(client_address);
   int r, i;

   r = accept(dpy->fd[0].fd, (struct sockaddr *) &client_address, &l);
   if (r < 0) {
      perror ("accept()");
      shut_fd(dpy,0);
      return False;
   } 


   /* Some rough & ready adaption of the XEvent semantics.
    */ 
   for (i = 1 ; i < dpy->nrFds ; i++) {
      if (dpy->fd[i].fd < 0) {
	 XEvent *er = queue_event(dpy);
	 if (!er) {
	    close(r);
	    return False;
	 }

	 dpy->fd[i].fd = r;
	 er->xcreatewindow.type = CreateNotify;
	 er->xcreatewindow.serial = 0;
	 er->xcreatewindow.send_event = 0;
	 er->xcreatewindow.display = dpy;
	 er->xcreatewindow.window = (Window)i;	/* fd slot == window, now? */

	 /* Send the driver client message - this is expected as the
	  * first message on a new connection.  The recpient already
	  * knows the size of the message.
	  */
	 welcome_message( dpy, i );
	 return True;
      }	    
   }

   fprintf(stderr, "[miniglx] %s: Max nr clients exceeded\n", __FUNCTION__);
   close(r);
   return False;
}

/* This routine "puffs out" the very basic communciations between
 * client & server to full-sized X Events that can be handled by the
 * application.
 */
static int
handle_fifo_read( Display *dpy, int i )
{
   char id = dpy->fd[i].readbuf[0];
   XEvent *er;
   int count = 1;

   /* read message id */
   /* read remainder of message (if any) */
   
   if (dpy->IsClient) {
      switch (id) {
	 /* The server has called 'XMapWindow' on a client window */
      case _YouveGotFocus:
	 er = queue_event(dpy);
	 if (!er) return False;
	 er->xmap.type = MapNotify;
	 er->xmap.serial = 0;
	 er->xmap.send_event = False;
	 er->xmap.display = dpy;
	 er->xmap.event = dpy->TheWindow;
	 er->xmap.window = dpy->TheWindow;
	 er->xmap.override_redirect = False;
	 break;

	 /* The server has called 'XMapWindow' or 'X???'  on a client
	  * window */
      case _RepaintPlease:
	 er = queue_event(dpy);
	 if (!er) return False;
	 er->xexpose.type = Expose;
	 er->xexpose.serial = 0;
	 er->xexpose.send_event = False;
	 er->xexpose.display = dpy;
	 er->xexpose.window = dpy->TheWindow;
	 if (dpy->rotateMode) {
	    er->xexpose.x = dpy->TheWindow->y;
	    er->xexpose.y = dpy->TheWindow->x;
	    er->xexpose.width = dpy->TheWindow->h;
	    er->xexpose.height = dpy->TheWindow->w;
	 }
	 else {
	    er->xexpose.x = dpy->TheWindow->x;
	    er->xexpose.y = dpy->TheWindow->y;
	    er->xexpose.width = dpy->TheWindow->w;
	    er->xexpose.height = dpy->TheWindow->h;
	 }
	 er->xexpose.count = 0;
	 break;

	 /* The server has called 'XUnmapWindow' on a client window */
      case _YouveLostFocus:
	 er = queue_event(dpy);
	 if (!er) return False;
	 er->xunmap.type = UnmapNotify;
	 er->xunmap.serial = 0;
	 er->xunmap.send_event = False;
	 er->xunmap.display = dpy;
	 er->xunmap.event = dpy->TheWindow;
	 er->xunmap.window = dpy->TheWindow;
	 er->xunmap.from_configure = False;
	 break;
	 
      default:
	 fprintf(stderr, "Client received unhandled message type %d\n", id);
	 shut_fd(dpy, i);		/* Actually shuts down the client */
	 return False;
      }
   }
   else {
      switch (id) {
	 /* Lets the server know that the client is ready to render
	  * (having called 'XMapWindow' locally).
	  */
      case _CanIHaveFocus:	 
	 er = queue_event(dpy);
	 if (!er) return False;
	 er->xmaprequest.type = MapRequest;
	 er->xmaprequest.serial = 0;
	 er->xmaprequest.send_event = False;
	 er->xmaprequest.display = dpy;
	 er->xmaprequest.parent = 0;
	 er->xmaprequest.window = (Window)i;
	 break;

	 /* Both _YouveLostFocus and _IDontWantFocus generate unmap
	  * events.  The idea is that _YouveLostFocus lets the client
	  * know that it has had focus revoked by the server, whereas
	  * _IDontWantFocus lets the server know that the client has
	  * unmapped its own window.
	  */
      case _IDontWantFocus:
	 er = queue_event(dpy);
	 if (!er) return False;
	 er->xunmap.type = UnmapNotify;
	 er->xunmap.serial = 0;
	 er->xunmap.send_event = False;
	 er->xunmap.display = dpy;
	 er->xunmap.event = (Window)i;
	 er->xunmap.window = (Window)i;
	 er->xunmap.from_configure = False;
	 break;

      default:
	 fprintf(stderr, "Server received unhandled message type %d\n", id);
	 shut_fd(dpy, i);		/* Generates DestroyNotify event */
	 return False;
      }
   }

   dpy->fd[i].readbuf_count -= count;

   /* This probably never happens, but just in case: */
   if (dpy->fd[i].readbuf_count) {
      fprintf(stderr, "count: %d memmove %p %p %d\n", count,
	      dpy->fd[i].readbuf + count,
	      dpy->fd[i].readbuf,
	      dpy->fd[i].readbuf_count);

      memmove(dpy->fd[i].readbuf + count,
	      dpy->fd[i].readbuf,
	      dpy->fd[i].readbuf_count);
   }

   return True;
}

#undef max
#define max(x,y) ((x) > (y) ? (x) : (y))

/* This all looks pretty complex, but is necessary especially on the
 * server side to prevent a poorly-behaved client from causing the
 * server to block in a read or write and hence not service the other
 * clients.
 *
 * See select_tut in the linux manual pages for more discussion.
 */
int 
__miniglx_Select( Display *dpy, int n, fd_set *rfds, fd_set *wfds, fd_set *xfds,
		  struct timeval *tv )
{
   int i;
   int retval;
   fd_set my_rfds, my_wfds;

   if (!rfds) {
      rfds = &my_rfds;
      FD_ZERO(rfds);
   }

   if (!wfds) {
      wfds = &my_wfds;
      FD_ZERO(wfds);
   }

   assert( dpy->eventqueue.head == dpy->eventqueue.tail );

   for (i = 0 ; i < dpy->nrFds; i++) {
      if (dpy->fd[i].fd < 0)
	 continue;
      
      if (dpy->fd[i].writebuf_count)
	 FD_SET(dpy->fd[i].fd, wfds);
	 
      if (dpy->fd[i].readbuf_count < MINIGLX_BUF_SIZE) 
	 FD_SET(dpy->fd[i].fd, rfds);
      
      n = max(n, dpy->fd[i].fd + 1);
   }


   retval = select( n, rfds, wfds, xfds, tv );
   if (retval < 0) 
      return retval;
   
   /* Handle server fd[0] specially:
    */
   if (!dpy->IsClient) {
      if (FD_ISSET(dpy->fd[0].fd, rfds)) {
	 FD_CLR(dpy->fd[0].fd, rfds);
	 handle_new_client( dpy );
      }
   }

   /* Otherwise, try and fill readbuffer and drain writebuffer:
    */
   for (i = 0 ; i < dpy->nrFds ; i++) {
      if (dpy->fd[i].fd < 0) 
	 continue;

      /* If there aren't any event slots left, don't examine
       * any more file events.  This will prevent lost events.
       */
      if (dpy->eventqueue.head == 
	  ((dpy->eventqueue.tail + 1) & MINIGLX_EVENT_QUEUE_MASK)) {
	 fprintf(stderr, "leaving event loop as event queue is full\n");
	 return retval;
      }

      if (FD_ISSET(dpy->fd[i].fd, wfds)) {
	 int r = write(dpy->fd[i].fd,
		       dpy->fd[i].writebuf,
		       dpy->fd[i].writebuf_count);
	 
	 if (r < 1) 
	    shut_fd(dpy,i);
	 else {
	    dpy->fd[i].writebuf_count -= r;
	    if (dpy->fd[i].writebuf_count) {
	       memmove(dpy->fd[i].writebuf + r,
		       dpy->fd[i].writebuf,
		       dpy->fd[i].writebuf_count);
	    }
	 }
      }

      if (FD_ISSET(dpy->fd[i].fd, rfds)) {
	 int r = read(dpy->fd[i].fd, 
		      dpy->fd[i].readbuf + dpy->fd[i].readbuf_count,
		      MINIGLX_BUF_SIZE - dpy->fd[i].readbuf_count);
	 
	 if (r < 1) 
	    shut_fd(dpy,i);
	 else {
	    dpy->fd[i].readbuf_count += r;
	 
	    fprintf(stderr, "Read %d bytes from fd[%d]\n", r, i);
	    handle_fifo_read( dpy, i );
	 }
      }
   }

   return retval;
}

static int handle_fd_events( Display *dpy, int nonblock )
{
   while (1) {
      struct timeval tv = {0, 0};
      int r = __miniglx_Select( dpy, 0, 0, 0, 0, nonblock ? &tv : 0 );
      if (r >= 0) 
	 return True;
      if (errno == EINTR || errno == EAGAIN)
	 continue;
      perror ("select()");
      exit (1);
   }
}



int __miniglx_open_connections( Display *dpy )
{
   struct sockaddr_un sa;
   int i;

   dpy->nrFds = dpy->IsClient ? 1 : MINIGLX_MAX_SERVER_FDS;
   dpy->fd = CALLOC( dpy->nrFds * sizeof(struct MiniGLXConnection));
   if (!dpy->fd)
      return False;

   for (i = 0 ; i < dpy->nrFds ; i++)
      dpy->fd[i].fd = -1;

   if (!dpy->IsClient) {
      if (unlink(MINIGLX_FIFO_NAME) != 0 && errno != ENOENT) { 
	 perror("unlink " MINIGLX_FIFO_NAME);
 	 return False; 
      } 
   } 

   /* Create a unix socket -- Note this is *not* a network connection!
    */
   dpy->fd[0].fd = socket(PF_UNIX, SOCK_STREAM, 0);
   if (dpy->fd[0].fd < 0) {
      perror("socket " MINIGLX_FIFO_NAME);
      return False;
   }

   memset(&sa, 0, sizeof(sa));
   sa.sun_family = AF_UNIX;
   strcpy(sa.sun_path, MINIGLX_FIFO_NAME);

   if (dpy->IsClient) {
      /* Connect to server
       */
      if (connect(dpy->fd[0].fd, (struct sockaddr *)&sa, sizeof(sa)) != 0) {
	 perror("connect");
	 shut_fd(dpy,0);
	 return False;
      }

      /* Wait for confirmation from the server, in the form of a _DriverInfo 
       * message.
       */
      welcome_message( dpy, 0 );
   }
   else {
      /* Bind socket to our filename
       */
      if (bind(dpy->fd[0].fd, (struct sockaddr *)&sa, sizeof(sa)) != 0) {
	 perror("bind");
	 shut_fd(dpy,0);
	 return False;
      }
      
      /* Listen for connections
       */
      if (listen(dpy->fd[0].fd, 5) != 0) {
	 perror("listen");
	 shut_fd(dpy,0);
	 return False;
      }
   }

   return True;
}


void __miniglx_close_connections( Display *dpy )
{
   int i;
   for (i = 0 ; i < dpy->nrFds ; i++)
      shut_fd( dpy, i );

   dpy->nrFds = 0;
   FREE(dpy->fd);
}

/**
 * \brief Map Window.
 *
 * \param display the display handle as returned by XOpenDisplay().
 * \param w the window handle.
 * 
 * If called by a client, sends a request for focus to the server.  If
 * called by the server, will generate a MapNotify and Expose event at
 * the client.
 * 
 */
void
XMapWindow( Display *dpy, Window w )
{
   if (dpy->IsClient) 
      send_char_msg( dpy, 0, _CanIHaveFocus );
   else {
      send_char_msg( dpy, (int)w, _YouveGotFocus );
      send_char_msg( dpy, (int)w, _RepaintPlease );
   }
}

/**
 * \brief Unmap Window.
 *
 * \param display the display handle as returned by XOpenDisplay().
 * \param w the window handle.
 * 
 * Should clients be allowed to unmap their own windows?  Probably, as
 * it is impossible to force them to keep updating their contents & at
 * least this way there is notification that they've stopped.
 * 
 */
void
XUnmapWindow( Display *dpy, Window window )
{
   send_char_msg( dpy, 0,  dpy->IsClient ? _IDontWantFocus : _YouveLostFocus );
}


int XNextEvent(Display *dpy, XEvent *event_return)
{
   for (;;) {
      if ( dpy->eventqueue.head != dpy->eventqueue.tail )
	 return dequeue_event( dpy, event_return ); 
      
      handle_fd_events( dpy, 0 );
   }
}

Bool XCheckMaskEvent(Display *dpy, long event_mask, XEvent *event_return)
{
   if ( dpy->eventqueue.head != dpy->eventqueue.tail )
      return dequeue_event( dpy, event_return ); 

   handle_fd_events( dpy, 1 );
 
   return dequeue_event( dpy, event_return ); 
}


Bool XCheckWindowEvent(Display *dpy, Window w, long event_mask, 
		       XEvent *event_return)
{
   if (!w || w != dpy->TheWindow) 
      return False;

   return XCheckMaskEvent( dpy, event_mask, event_return );
}




/*@}*/
