// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

#include <asm/unistd.h>
#define MAX_ERRNO 4095

#ifndef TRANSFORM
#define TRANSFORM 17h
#endif

.extern	__set_errno_internal_tfs

.align 4
.globl syscall4_tfs, hidden
.hidden syscall4_tfs
.text
syscall4_tfs:
	movq    %rcx, %r10
	//movl    $__NR_mmap, %eax
	movq	%r8, %rax
	subq	$TRANSFORM, %rax
	syscall
	cmpq    $-MAX_ERRNO, %rax
	jb      1f
	negl    %eax
	movl    %eax, %edi
	call    __set_errno_internal_tfs
1:
	ret

.align 4
.globl mmap_tfs, hidden
.hidden mmap_tfs
.text
mmap_tfs:
	movq    %rcx, %r10
	movl    $__NR_mmap, %eax
	syscall
	cmpq    $-MAX_ERRNO, %rax
	jb      1f
	negl    %eax
	movl    %eax, %edi
	call    __set_errno_internal_tfs
1:
	ret


.align 4
.globl pread_tfs, hidden
.hidden pread_tfs
.text
pread_tfs:
	movq    %rcx, %r10
	movl    $__NR_pread64, %eax
	syscall
	cmpq    $-MAX_ERRNO, %rax
	jb      1f
	negl    %eax
	movl    %eax, %edi
	call    __set_errno_internal_tfs
1:
	ret

.align 4
.globl pwrite_tfs, hidden
.hidden pwrite_tfs
.text
pwrite_tfs:
	movq    %rcx, %r10
	movl    $__NR_pwrite64, %eax
	syscall
	cmpq    $-MAX_ERRNO, %rax
	jb      1f
	negl    %eax
	movl    %eax, %edi
	call    __set_errno_internal_tfs
1:
	ret


.align 4
.globl ppoll_tfs, hidden
.hidden ppoll_tfs
.text
ppoll_tfs:
	movq    %rcx, %r10
	movl    $__NR_ppoll, %eax
	syscall
	cmpq    $-MAX_ERRNO, %rax
	jb      1f
	negl    %eax
	movl    %eax, %edi
	call    __set_errno_internal_tfs
1:
	ret


.align 4
.globl ftruncate_tfs, hidden
.hidden ftruncate_tfs
.text
ftruncate_tfs:
	movq    %rcx, %r10
	movl    $__NR_ftruncate, %eax
	syscall
	cmpq    $-MAX_ERRNO, %rax
	jb      1f
	negl    %eax
	movl    %eax, %edi
	call    __set_errno_internal_tfs
1:
	ret

