Name

    MESA_agp_offset

Name Strings

    GLX_MESA_agp_offset

Contact

    Brian Paul, Tungsten Graphics, Inc. (brian 'at' tungstengraphics.com)
    Keith Whitwell, Tungsten Graphics, Inc.  (keith 'at' tungstengraphics.com)

Status

    Shipping (Mesa 4.0.4 and later)

Version

    1.0

Number

    TBD

Dependencies

    OpenGL 1.0 or later is required
    GLX_NV_vertex_array_range is required.
    This extensions is written against the OpenGL 1.4 Specification.

Overview

    This extensions provides a way to convert pointers in an AGP memory region
    into byte offsets into the AGP apeture.

IP Status

    None

Issues

    None

New Procedures and Functions

    uint glXGetAGPOffsetMESA( const void *pointer )

New Tokens

    None

Additions to the OpenGL 1.4 Specification

    None

Additions to Chapter ??? the GLX 1.4 Specification (??? chapter name)

    XXX to do


GLX Protocol

    None.  This is a client side-only extension.

Errors

    glXGetAGPOffsetMESA will return ~0 if the pointer does not point to
    an AGP memory region.

New State

    None

Revision History

    20 September 2002 - Initial draft
