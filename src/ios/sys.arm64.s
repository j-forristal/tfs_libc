// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

#include "sys.arm64.h"

#ifndef TRANSFORM
#define TRANSFORM 23
#endif

.extern _set_errno_internal_tfs

.align 4
.global _syscall4_tfs
.text
_syscall4_tfs:
	mov		x16, x4
	sub     	x16, x16, #TRANSFORM
        svc             #SWI_SYSCALL
	b.cs		1f
	ret
1:
	b		_set_errno_internal_tfs

