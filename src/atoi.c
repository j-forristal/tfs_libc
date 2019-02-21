// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

#include <stdint.h>
#include <stddef.h>

int atoi_tfs( const char *s, int max)
{
        int i, rc = 0;
        for( i=0; i<max; i++){
                if( s[i] < '0' || s[i] > '9' ) break;
                rc = (rc * 10) + (s[i] - '0');
        }
        return rc;
}
