// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

#include "sys.arm.h"

#ifndef TRANSFORM
#define TRANSFORM 23
#endif

.extern _set_errno_internal_tfs

.align 2
.globl _syscall4_tfs
.text
_syscall4_tfs:
	// r0 - r3 are setup
	// r4 (on stack) is the syscall number
	ldr             ip, [sp]
	sub		ip, ip, #TRANSFORM
	svc             #SWI_SYSCALL
        bxcc 		lr 
1:	b _set_errno_internal_tfs




