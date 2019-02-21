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
	pushl   %ebx
	pushl   %ecx
	pushl   %edx
	pushl   %esi
	pushl   %edi
	pushl   %ebp
	mov     28(%esp), %ebx
	mov     32(%esp), %ecx
	mov     36(%esp), %edx
	mov     40(%esp), %esi
	// This is the syscall num:
	mov     44(%esp), %eax
	subl	$TRANSFORM, %eax
	int     $0x80
	cmpl    $-MAX_ERRNO, %eax
	jb      1f
	negl    %eax
	pushl   %eax
	call    __set_errno_internal_tfs
	addl    $4, %esp
1:
	popl    %ebp
	popl    %edi
	popl    %esi
	popl    %edx
	popl    %ecx
	popl    %ebx
	ret



.align 4
.globl mmap_tfs, hidden
.hidden mmap_tfs
.text
mmap_tfs:
	pushl   %ebx
	pushl   %ecx
	pushl   %edx
	pushl   %esi
	pushl   %edi
	pushl   %ebp
	mov     28(%esp), %ebx
	mov     32(%esp), %ecx
	mov     36(%esp), %edx
	mov     40(%esp), %esi
	mov     44(%esp), %edi
	mov     48(%esp), %ebp
	movl    $__NR_mmap2, %eax
	int     $0x80
	cmpl    $-MAX_ERRNO, %eax
	jb      1f
	negl    %eax
	pushl   %eax
	call    __set_errno_internal_tfs
	addl    $4, %esp
1:
	popl    %ebp
	popl    %edi
	popl    %esi
	popl    %edx
	popl    %ecx
	popl    %ebx
	ret


.align 4
.globl pread_tfs, hidden
.hidden pread_tfs
.text
pread_tfs:
	pushl   %ebx
	pushl   %ecx
	pushl   %edx
	pushl   %esi
	pushl   %edi
	pushl   %ebp
	mov     28(%esp), %ebx
	mov     32(%esp), %ecx
	mov     36(%esp), %edx
	mov     40(%esp), %esi
	mov     44(%esp), %edi
	mov     48(%esp), %ebp
	movl    $__NR_pread64, %eax
	int     $0x80
	cmpl    $-MAX_ERRNO, %eax
	jb      1f
	negl    %eax
	pushl   %eax
	call    __set_errno_internal_tfs
	addl    $4, %esp
1:
	popl    %ebp
	popl    %edi
	popl    %esi
	popl    %edx
	popl    %ecx
	popl    %ebx
	ret

.align 4
.globl pwrite_tfs, hidden
.hidden pwrite_tfs
.text
pwrite_tfs:
	pushl   %ebx
	pushl   %ecx
	pushl   %edx
	pushl   %esi
	pushl   %edi
	pushl   %ebp
	mov     28(%esp), %ebx
	mov     32(%esp), %ecx
	mov     36(%esp), %edx
	mov     40(%esp), %esi
	mov     44(%esp), %edi
	mov     48(%esp), %ebp
	movl    $__NR_pwrite64, %eax
	int     $0x80
	cmpl    $-MAX_ERRNO, %eax
	jb      1f
	negl    %eax
	pushl   %eax
	call    __set_errno_internal_tfs
	addl    $4, %esp
1:
	popl    %ebp
	popl    %edi
	popl    %esi
	popl    %edx
	popl    %ecx
	popl    %ebx
	ret

.align 4
.globl ppoll_tfs, hidden
.hidden ppoll_tfs
.text
ppoll_tfs:
	pushl   %ebx
	pushl   %ecx
	pushl   %edx
	pushl   %esi
	pushl   %edi
	pushl   %ebp
	mov     28(%esp), %ebx
	mov     32(%esp), %ecx
	mov     36(%esp), %edx
	mov     40(%esp), %esi
	mov     44(%esp), %edi
	mov     48(%esp), %ebp
	movl    $__NR_ppoll, %eax
	int     $0x80
	cmpl    $-MAX_ERRNO, %eax
	jb      1f
	negl    %eax
	pushl   %eax
	call    __set_errno_internal_tfs
	addl    $4, %esp
1:
	popl    %ebp
	popl    %edi
	popl    %esi
	popl    %edx
	popl    %ecx
	popl    %ebx
	ret


.align 4
.globl ftruncate_tfs, hidden
.hidden ftruncate_tfs
.text
ftruncate_tfs:
	pushl   %ebx
	pushl   %ecx
	pushl   %edx
	pushl   %esi
	pushl   %edi
	pushl   %ebp
	mov     28(%esp), %ebx
	mov     32(%esp), %ecx
	mov     36(%esp), %edx
	mov     40(%esp), %esi
	mov     44(%esp), %edi
	mov     48(%esp), %ebp
	movl    $__NR_ftruncate64, %eax
	int     $0x80
	cmpl    $-MAX_ERRNO, %eax
	jb      1f
	negl    %eax
	pushl   %eax
	call    __set_errno_internal_tfs
	addl    $4, %esp
1:
	popl    %ebp
	popl    %edi
	popl    %esi
	popl    %edx
	popl    %ecx
	popl    %ebx
	ret

