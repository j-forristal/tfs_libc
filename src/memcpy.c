// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

/* memcpy( void *, const void *, size_t )
   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdint.h>
#include <stddef.h>

void* memcpy_tfs( void *s1, const void *s2, size_t n )
{
    uint8_t *dest = (uint8_t*) s1;
    const uint8_t* src = (const uint8_t*) s2;
    while ( n-- )
    {
        *dest++ = *src++;
    }
    return s1;
}
