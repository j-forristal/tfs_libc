// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

#include <asm/unistd.h>
#define MAX_ERRNO 4095

#ifndef TRANSFORM
#define TRANSFORM 23
#endif


.extern	__set_errno_internal_tfs

.align 2
.globl syscall4_tfs
.hidden syscall4_tfs
.text
syscall4_tfs:
	// preserve r0 - r3 (first 4 args)
	// syscall num is first val on stack (5th arg)
	mov	ip, sp
	stmfd	sp!, {r7}
	ldmfd	ip, {r7}
	sub	r7, r7, #TRANSFORM
	swi	#0
	ldmfd	sp!, {r7}
	cmn	r0, #(MAX_ERRNO + 1)
	bxls	lr
	neg	r0, r0
	b	__set_errno_internal_tfs

.align 2
.globl mmap_tfs
.hidden mmap_tfs
.text
mmap_tfs:
	mov     ip, sp
	stmfd   sp!, {r4, r5, r6, r7}
	ldmfd   ip, {r4, r5, r6}
	ldr     r7, =__NR_mmap2
	swi     #0
	ldmfd   sp!, {r4, r5, r6, r7}
	cmn     r0, #(MAX_ERRNO + 1)
	bxls    lr
	neg     r0, r0
	b       __set_errno_internal_tfs


.align 2
.globl pread_tfs
.hidden pread_tfs
.text
pread_tfs:
	mov     ip, sp
	stmfd   sp!, {r4, r5, r6, r7}
	ldr     r7, =__NR_pread64
	b	pio_tfs

.align 2
.globl pwrite_tfs
.hidden pwrite_tfs
.text
pwrite_tfs:
	mov     ip, sp
	stmfd   sp!, {r4, r5, r6, r7}
	ldr     r7, =__NR_pwrite64
	b	pio_tfs

.align 2
.text
pio_tfs:
	ldmfd   ip, {r4, r5, r6}
	swi     #0
	ldmfd   sp!, {r4, r5, r6, r7}
	cmn     r0, #(MAX_ERRNO + 1)
	bxls    lr
	neg     r0, r0
	b       __set_errno_internal_tfs


.align 2
.globl ppoll_tfs
.hidden ppoll_tfs
.text
ppoll_tfs:
	mov     ip, sp
	stmfd   sp!, {r4, r5, r6, r7}
	ldmfd   ip, {r4, r5, r6}
	ldr     r7, =__NR_ppoll
	swi     #0
	ldmfd   sp!, {r4, r5, r6, r7}
	cmn     r0, #(MAX_ERRNO + 1)
	bxls    lr
	neg     r0, r0
	b       __set_errno_internal_tfs

.align 2
.globl ftruncate_tfs
.hidden ftruncate_tfs
.text
ftruncate_tfs:
	mov     ip, sp
	stmfd   sp!, {r4, r5, r6, r7}
	ldmfd   ip, {r4, r5, r6}
	ldr     r7, =__NR_ftruncate64
	swi     #0
	ldmfd   sp!, {r4, r5, r6, r7}
	cmn     r0, #(MAX_ERRNO + 1)
	bxls    lr
	neg     r0, r0
	b       __set_errno_internal_tfs

