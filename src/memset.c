// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

/* memset( void *, int, size_t )
   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdint.h>
#include <stddef.h>

void* memset_tfs( void *s, int c, size_t n )
{
    uint8_t* p = (uint8_t*) s;
    while ( n-- )
    {
        *p++ = (uint8_t) c;
    }
    return s;
}
