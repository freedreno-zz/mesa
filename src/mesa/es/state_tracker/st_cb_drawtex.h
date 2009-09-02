/**************************************************************************
 * 
 * Copyright 2008 Tungsten Graphics, Inc., Cedar Park, Texas.
 * All Rights Reserved.
 *
 **************************************************************************/


#ifndef ST_CB_DRAWTEX_H
#define ST_CB_DRAWTEX_H


struct st_context;


extern void
_mesa_DrawTexf(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);


extern void
_mesa_DrawTexfv(const GLfloat *coords);


extern void
st_destroy_drawtex(struct st_context *st);


#endif
