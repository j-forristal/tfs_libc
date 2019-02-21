// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#define TIME(t)			time(t)

int atoi_tfs(const char* a,int b);
int itoa_tfs(unsigned int a,char* b);
#define ATOI(a,b)		atoi_tfs(a,b)
#define ITOA(a,b)		itoa_tfs(a,b)


#include <string.h>
#define TFMEMCPY(d,s,n)           memcpy(d,s,n)
#define MEMSET(b,c,l)           memset(b,c,l)
#define MEMSET_REF              memset
#define MEMCMP(s1,s2,n)         memcmp(s1,s2,n)
#define STRLEN(s)               strlen(s)
#define STRSTR(a,b)             strstr(a,b)


#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#define CLOSE(f)		close(f)
#define FSTAT(f,s)		fstat(f,s)
#define FSTATAT(d,f,s,o)	fstatat(d,f,s,o)
//#define MKDIR(p,m)		mkdirat(AT_FDCWD,p,m)
#define MKDIR(p,m)		mkdir(p,m)
#define READ(d,b,n) 		read(d,b,n)
#define PREAD(d,b,n,o) 		pread(d,b,n,o)
#define WRITE(d,b,n) 		write(d,b,n)
#define PWRITE(d,b,n,o) 	pwrite(d,b,n,o)
#define FSYNC(f) 		fsync(f)
#define FTRUNCATE(f,l) 		ftruncate(f,l)
#define FCNTL(f,c,v)		fcntl(f,c,v)
#define FLOCK(f,o)		flock(f,o)
#define STATFS(p,b)		statfs(p,b)
#define ACCESS(p,m)		access(p,m)
#define FACCESSAT(d,p,m,f)	faccessat(d,p,m,f)
#define OPEN(p,f,m)		open(p,f,m)
#define OPENAT(d,p,f,m)		openat(d,p,f,m)
#define UNLINK(p)		unlinkat(AT_FDCWD,p,0)
#define PIPE2(a,f)		pipe2(a,f)

#include <sys/mman.h>
#define MMAP_NOM		mmap
#define MMAP(a,l,p,f,fd,o)	mmap(a,l,p,f,fd,o)
#define MUNMAP(a,l)		munmap(a,l)
#define MPROTECT_NOM		mprotect
#define MPROTECT(a,l,p)		mprotect(a,l,p)

#include <stdlib.h>
#define MALLOC(l)		malloc(l)
#define FREE(a)			free(a)

#include <assert.h>
#define ASSERT(...)		assert(__VA_ARGS__)

#define ABORT() do { ASSERT(0); abort(); } while(0)

#include <poll.h>
#define POLL(f,n,t)		poll(f,n,t)

#include <sys/socket.h>
#define RECV(s,b,l,f)		recv(s,b,l,f)
#define SEND(s,b,l,f)		send(s,b,l,f)
#define SENDMSG(s,m,f)		sendmsg(s,m,f)
#define GETPEERNAME(s,a,l)	getpeername(s,a,l)
#define SOCKET(d,t,p)		socket(d,t,p)
#define CONNECT(s,a,l)		connect(s,a,l)
#define BIND(s,a,l)             bind(s,a,l)
#define ACCEPT(s,a,l)           accept(s,a,l)
#define SETSOCKOPT(s,o,n,v,l)   setsockopt(s,o,n,v,l)

#include <sys/syscall.h>
#define SYSCALL(n, ...)		syscall(n, __VA_ARGS__)
// Libc fixup: just use standard syscall for our specialized syscalls
#define syscall4_tfs		syscall

#include <sys/sysctl.h>
#define SYSCTL_NOM              sysctl
#define SYSCTL(...)		sysctl(__VA_ARGS__)

// Generic IOS support:
#define CSOPS_NOM               syscall
#define CSOPS(a,b,c,d)          ((int)syscall((uintptr_t)a,(uintptr_t)b,(uintptr_t)c,(uintptr_t)d,SYS_csops))


// NOTE: inotify is not on all platforms; we can include
// defines here that may never be used, as long as they
// don't have tendrils to headers, etc.  Caller must
// include inotify.h
#define INOTIFY_INIT()		inotify_init()
#define INOTIFY_ADD_WATCH(f,p,m)	inotify_add_watch(f,p,m)


// Linux particular tee()/splice()/vmsplice() support
#define SPLICE(a,b,c,d,e,f)		splice(a,b,c,d,e,f)
#define VMSPLICE(a,b,c,d)		vmsplice(a,b,c,d)
#define TEE(a,b,c,d)			tee(a,b,c,d)

#endif
