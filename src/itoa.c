// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

#include <stdint.h>
#include <stddef.h>

int itoa_tfs(unsigned int n, char *s)
{
        int j = 0, i, r;
        char c;

        // convert to chars
        do { s[j] = n % 10 + '0'; j++; } while ((n/=10) > 0);
        s[j] = 0;
	r = j;

        // reverse()
        for( i=0, j=j-1; i<j; i++, j-- ){
                c = s[i];
                s[i] = s[j];
                s[j] = c;
        }
        return r;
}
