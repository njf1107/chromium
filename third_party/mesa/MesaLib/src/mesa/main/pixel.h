/*
 * Mesa 3-D graphics library
 * Version:  7.1
 *
 * Copyright (C) 1999-2008  Brian Paul   All Rights Reserved.
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


/**
 * \file pixel.h
 * Pixel operations.
 */


#ifndef PIXEL_H
#define PIXEL_H


#include "main/mtypes.h"


#if FEATURE_pixel_transfer

extern void 
_mesa_update_pixel( GLcontext *ctx, GLuint newstate );

extern void
_mesa_init_pixel_dispatch( struct _glapi_table * disp );

#else /* FEATURE_pixel_transfer */

static INLINE void
_mesa_update_pixel(GLcontext *ctx, GLuint newstate)
{
}

static INLINE void
_mesa_init_pixel_dispatch(struct _glapi_table *disp)
{
}

#endif /* FEATURE_pixel_transfer */


extern void 
_mesa_init_pixel( GLcontext * ctx );

/*@}*/

#endif /* PIXEL_H */
