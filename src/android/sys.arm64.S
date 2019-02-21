// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

// Code modeled on http://androidxref.com/6.0.1_r10/xref/bionic/libc/arch-arm64/syscalls/mmap.S

#include <asm/unistd.h>
#define MAX_ERRNO 4095

#ifndef TRANSFORM
#define TRANSFORM 23
#endif

.extern	__set_errno_internal_tfs

.align 4
.globl syscall4_tfs
.hidden syscall4_tfs
.text
syscall4_tfs:
	// preserve x0 - x3 (first 4 args)
	// syscall num is in x4
	mov	x8, x4
	sub	x8, x8, #TRANSFORM
	svc	#0
	cmn	x0, #(MAX_ERRNO + 1)
	cneg	x0, x0, hi
	b.hi	__set_errno_internal_tfs
	ret

.align 4
.globl mmap_tfs
.hidden mmap_tfs
.text
mmap_tfs:
	mov	x8, __NR_mmap
	svc	#0
	cmn	x0, #(MAX_ERRNO + 1)
	cneg	x0, x0, hi
	b.hi	__set_errno_internal_tfs
	ret

.align 4
.globl pread_tfs
.hidden pread_tfs
.text
pread_tfs:
	mov	x8, __NR_pread64
	b	pio_tfs

.align 4
.globl pwrite_tfs
.hidden pwrite_tfs
.text
pwrite_tfs:
	mov	x8, __NR_pwrite64
	b	pio_tfs

.align 4
.text
pio_tfs:
	svc	#0
	cmn	x0, #(MAX_ERRNO + 1)
	cneg	x0, x0, hi
	b.hi	__set_errno_internal_tfs
	ret
	

.align 4
.globl ppoll_tfs
.hidden ppoll_tfs
.text
ppoll_tfs:
	mov	x8, __NR_ppoll
	svc	#0
	cmn	x0, #(MAX_ERRNO + 1)
	cneg	x0, x0, hi
	b.hi	__set_errno_internal_tfs
	ret

.align 4
.globl ftruncate_tfs
.hidden ftruncate_tfs
.text
ftruncate_tfs:
	mov	x8, __NR_ftruncate
	svc	#0
	cmn	x0, #(MAX_ERRNO + 1)
	cneg	x0, x0, hi
	b.hi	__set_errno_internal_tfs
	ret

