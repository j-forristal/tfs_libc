// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

#ifndef _SYS_H_
#define _SYS_H_

// https://github.com/darwin-on-arm/xnu/blob/master/libsyscall/custom/SYS.h

#include <sys/syscall.h>

#define SWI_SYSCALL 0x80

#if defined(__arm__)

#define MI_GET_ADDRESS(reg,var)  \
	ldr	reg, 3f	;\
	b	4f	;\
3:	.long var	;\
4:

#define MI_BRANCH_EXTERNAL(var)	;\
	.globl	var	;\
 	b	var

#define MI_CALL_EXTERNAL(var)	\
	.globl	var	;\
 	bl	var

#define DO_SYSCALL(num)		\
	.if (((num) & 0xff) == (num)) 	       		;\
	mov		ip, #(num)	 		;\
	.elseif (((num) & 0x3fc) == (num))		;\
	mov		ip, #(num)			;\
	.else						;\
	mov		ip, #((num) & 0xffffff00)	;\
	orr		ip, ip, #((num) & 0xff)	;\
	.endif						;\
	swi		#SWI_SYSCALL


#define	SYSCALL_NONAME_0to4(name)		\
	DO_SYSCALL(SYS_##name)			;\
	bxcc lr					;\
1:	MI_BRANCH_EXTERNAL(cerror_tfs)		

#define	SYSCALL_NONAME_5(name)			\
	mov		ip, sp 			;\
	stmfd	sp!, { r4-r5 }			;\
	ldr		r4, [ip]		;\
	DO_SYSCALL(SYS_##name)			;\
	ldmfd	sp!, { r4-r5 }			;\
	bxcc		lr			;\
1:	MI_BRANCH_EXTERNAL(cerror_tfs)	

#define	SYSCALL_NONAME_6to8(name, save_regs, arg_regs)	\
	mov		ip, sp 			;\
	stmfd	sp!, { save_regs }		;\
	ldmia	ip, { arg_regs }		;\
	DO_SYSCALL(SYS_##name)			;\
	ldmfd	sp!, { save_regs }		;\
	bxcc		lr			;\
1:	MI_BRANCH_EXTERNAL(cerror_tfs)	

#define SYSCALL_NONAME_0(name)		SYSCALL_NONAME_0to4(name)
#define SYSCALL_NONAME_1(name)		SYSCALL_NONAME_0to4(name)
#define SYSCALL_NONAME_2(name)		SYSCALL_NONAME_0to4(name)
#define SYSCALL_NONAME_3(name)		SYSCALL_NONAME_0to4(name)
#define SYSCALL_NONAME_4(name)		SYSCALL_NONAME_0to4(name)
#define SYSCALL_NONAME_6(name)		SYSCALL_NONAME_6to8(name, r4-r5, r4-r5)
#define SYSCALL_NONAME_7(name)		SYSCALL_NONAME_6to8(name, r4-r6 COMMA r8, r4-r6)
#define SYSCALL_NONAME_8(name)		SYSCALL_NONAME_6to8(name, r4-r6 COMMA r8, r4-r6 COMMA r8)


#endif

#endif
