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

/* $Id: miniglx_events.c,v 1.1.2.1 2003/04/15 11:01:27 keithw Exp $ */


/**
 * \file miniglx_fifo.c
 * \brief Mini GLX client/server communication functions.
 * \author Keith Whitwell
 *
 * The Mini GLX interface is a subset of the GLX interface, plus a
 * minimal set of Xlib functions.  This file adds interfaces to
 * arbitrate a single cliprect between multiple direct rendering
 * clients.
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

static int handle_fifo_read( Display *dpy, int i );

#define MINIGLX_FIFO_NAME "/tmp/miniglx.fifo"


enum msgs {
   _CanIHaveFocus = 0,
   _IDontWantFocus = 1,
   _YouveGotFocus = 2,
   _YouveLostFocus = 3,
   _RepaintPlease = 4,
   _MaxMsg
};

static XEvent *queue_event( Display *dpy )
{
   int incr = (dpy->eventqueue.tail + 1) & MINIGLX_EVENT_QUEUE_MASK;
   if (incr == dpy->eventqueue.head)
      return 0;
   else {
      dpy->eventqueue.nr++;
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
      dpy->eventqueue.nr--;
      return True;
   }
}


/* A fairly complete client/server non-blocking communication
 * mechanism.  Probably overkill given that none of our messages
 * currently exceed 1 byte in length.
 */
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
   er->xdestroywindow.window = i;	
}


int __miniglx_OpenClientServerConnection( Display *dpy )
{
   struct sockaddr_un sa;
   int i;

   memset(&dpy, 0, sizeof(dpy));
   for (i = 0 ; i < MINIGLX_MAX_FDS ; i++)
      dpy->fd[i].fd = -1;

   if (!dpy->IsClient) {
      if (unlink(MINIGLX_FIFO_NAME) != 0 && errno != ENOENT) { 
	 perror("unlink " MINIGLX_FIFO_NAME);
 	 return GL_FALSE; 
      } 
   } 

   /* Create a unix socket -- Note this is *not* a network connection!
    */
   dpy->fd[0].fd = socket(PF_UNIX, SOCK_STREAM, 0);
   if (dpy->fd[0].fd < 0) {
      perror("socket " MINIGLX_FIFO_NAME);
      return GL_FALSE;
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
	 return GL_FALSE;
      }
   }
   else {
      /* Bind it to our filename
       */
      if (bind(dpy->fd[0].fd, (struct sockaddr *)&sa, sizeof(sa)) != 0) {
	 perror("bind");
	 shut_fd(dpy,0);
	 return GL_FALSE;
      }
      
      /* Listen for connections
       */
      if (listen(dpy->fd[0].fd, 5) != 0) {
	 perror("listen");
	 shut_fd(dpy,0);
	 return GL_FALSE;
      }
   }

   return GL_TRUE;
}

static int handle_new_client( Display *dpy )
{
   XEvent *er;
   unsigned int l;
   struct sockaddr_un client_address;
   int r, i;

   r = accept(dpy->fd[0].fd, (struct sockaddr *) &client_address, &l);
   if (r < 0) {
      perror ("accept()");
      shut_fd(dpy,0);
      return GL_FALSE;
   } 

   er = queue_event(dpy);
   if (!er) {
      close(r);
      return GL_FALSE;
   }

   for (i = 0 ; er && i < MINIGLX_MAX_FDS ; i++) {
      if (dpy->fd[i].fd < 0) {
	 dpy->fd[i].fd = r;
	 er->xcreatewindow.type = CreateNotify;
	 er->xcreatewindow.serial = 0;
	 er->xcreatewindow.send_event = 0;
	 er->xcreatewindow.display = dpy;
	 er->xcreatewindow.window = i;	/* fd slot == window, now? */
	 return GL_TRUE;
      }	    
   }

   fprintf(stderr, "[miniglx] %s: Max nr clients exceeded\n", __FUNCTION__);
   close(r);
   return GL_FALSE;
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
static int 
handle_fd_events( Display *dpy, int nonblock )
{
   int i;
   int retval = GL_FALSE;

   assert( dpy->eventqueue.head == dpy->eventqueue.tail );

   do { 
      fd_set rfds, wfds;
      struct timeval tv;
      int n = 0, r;
      
      FD_ZERO(&rfds);
      FD_ZERO(&wfds);
      tv.tv_sec = 0;
      tv.tv_usec = 0;

      for (i = 0 ; i < MINIGLX_MAX_FDS; i++) {
	 if (dpy->fd[i].fd < 0)
	    continue;

	 if (dpy->fd[i].writebuf_count)
	    FD_SET(dpy->fd[i].fd, &wfds);
	 
	 if (dpy->fd[i].readbuf_count < MINIGLX_BUF_SIZE) 
	    FD_SET(dpy->fd[i].fd, &rfds);

	 n = max(n, dpy->fd[i].fd);
      }


      r = select(n+1, &rfds, &wfds, NULL, nonblock ? &tv : NULL);
      if (r < 0) {
	 if (errno == EINTR || errno == EAGAIN)
	    continue;
	 perror ("select()");
	 exit (1);
      }

      /* Handle server fd[0] specially:
       */
      if (!dpy->IsClient) {
	 if (FD_ISSET(dpy->fd[0].fd, &rfds)) {
	    FD_CLR(dpy->fd[0].fd, &rfds);
	    if (handle_new_client( dpy )) {
	       retval = GL_TRUE;     /* new events for application */
	       nonblock = 1;         /* exit with new events after this loop */
	    }	     
	 }
      }

      /* Otherwise, try and fill readbuffer and drain writebuffer:
       */
      for (i = 0 ; i < MINIGLX_MAX_FDS ; i++) {
	 if (dpy->fd[i].fd < 0) 
	    continue;

	 /* If there aren't any event slots left, don't examine
	  * any more file events.  This will prevent lost events.
	  */
	 if (dpy->eventqueue.nr >= MINIGLX_EVENT_QUEUE_SZ - 2) {
	    fprintf(stderr, "leaving event loop as event queue is full\n");
	    return retval;
	 }

	 if (FD_ISSET(dpy->fd[i].fd, &wfds)) {
	    r = write(dpy->fd[i].fd,
		      dpy->fd[i].writebuf,
		      dpy->fd[i].writebuf_count);

	    if (r < 1) 
	       shut_fd(dpy,i);
	    else {
	       dpy->fd[i].writebuf_count -= r;
	       /* This probably never happens, but just in case: */
	       if (dpy->fd[i].writebuf_count) {
		  memmove(dpy->fd[i].writebuf + r,
			  dpy->fd[i].writebuf,
			  dpy->fd[i].writebuf_count);
	       }
	    }
	 }

	 if (FD_ISSET(dpy->fd[i].fd, &rfds)) {
	    r = read(dpy->fd[i].fd, 
		     dpy->fd[i].readbuf + dpy->fd[i].readbuf_count,
		     MINIGLX_BUF_SIZE - dpy->fd[i].readbuf_count);

	    if (r < 1) 
	       shut_fd(dpy,i);
	    else
	       dpy->fd[i].readbuf_count += r;
	    
	    if (handle_fifo_read( dpy, i )) {
	       retval = GL_TRUE;     /* new events for application */
	       nonblock = 1;         /* exit with new events after this loop */
	    }	     
	 }
      }
   } while (!nonblock);

   return retval;
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

   /* read message id */
   /* read remainder of message (if any) */
   
   if (dpy->IsClient) {
      switch (id) {
	 /* The server has called 'XMapWindow' on a client window */
      case _YouveGotFocus:
	 er = queue_event(dpy);
	 if (!er) return GL_FALSE;
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
	 if (!er) return GL_FALSE;
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
	 if (!er) return GL_FALSE;
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
	 break;
      }
   }
   else {
      switch (id) {
	 /* Lets the server know that the client is ready to render
	  * (having called 'XMapWindow' locally).
	  */
      case _CanIHaveFocus:	 
	 er = queue_event(dpy);
	 if (!er) return GL_FALSE;
	 er->xmaprequest.type = MapRequest;
	 er->xmaprequest.serial = 0;
	 er->xmaprequest.send_event = False;
	 er->xmaprequest.display = dpy;
	 er->xmaprequest.parent = 0;
	 er->xmaprequest.window = i;
	 break;

	 /* Both _YouveLostFocus and _IDontWantFocus generate unmap
	  * events.  The idea is that _YouveLostFocus lets the client
	  * know that it has had focus revoked by the server, whereas
	  * _IDontWantFocus lets the server know that the client has
	  * unmapped its own window.
	  */
      case _IDontWantFocus:
	 er = queue_event(dpy);
	 if (!er) return GL_FALSE;
	 er->xunmap.type = UnmapNotify;
	 er->xunmap.serial = 0;
	 er->xunmap.send_event = False;
	 er->xunmap.display = dpy;
	 er->xunmap.event = i;
	 er->xunmap.window = i;
	 er->xunmap.from_configure = False;
	 break;
      default:
	 fprintf(stderr, "Server received unhandled message type %d\n", id);
	 shut_fd(dpy, i);		/* Generates DestroyNotify event */
	 break;
      }
   }

   return GL_TRUE;
}

int XNextEvent(Display *dpy, XEvent *event_return)
{
   for (;;) {
      if ( dpy->eventqueue.head != dpy->eventqueue.tail )
	 return dequeue_event( dpy, event_return ); 
      
      handle_fd_events( dpy, 0 );
   }
}


Bool XCheckWindowEvent(Display *dpy, Window w, long event_mask, 
		       XEvent *event_return)
{
   if (!w || w != dpy->TheWindow) 
      return False;

   if ( dpy->eventqueue.head != dpy->eventqueue.tail )
      return dequeue_event( dpy, event_return ); 

   handle_fd_events( dpy, 1 );
 
   return dequeue_event( dpy, event_return ); 
}



/*@}*/
