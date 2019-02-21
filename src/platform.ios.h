// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#ifndef TRANSFORM
#define TRANSFORM 23
#endif

#define TIME(t)			time(t)

int atoi_tfs(const char* a,int b);
int itoa_tfs(unsigned int a,char* b);
#define ATOI(a,b)		atoi_tfs(a,b)
#define ITOA(a,b)		itoa_tfs(a,b)


#include <string.h>

void* memcpy_tfs(void *dst, const void *src, size_t n);
#define TFMEMCPY(d,s,n)           memcpy_tfs(d,s,n)

void* memset_tfs( void *b, int c, size_t len);
#define MEMSET(b,c,l)           memset_tfs(b,c,l)
#define MEMSET_REF              memset_tfs

int memcmp_tfs(const void *s1, const void *s2, size_t n);
#define MEMCMP(s1,s2,n)         memcmp_tfs(s1,s2,n)

size_t strlen_tfs(const char *s);
#define STRLEN(s)               strlen_tfs(s)

char* strstr_tfs(const char *a, const char *b);
#define STRSTR(a,b)             strstr_tfs(a,b)


#include <stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>

ssize_t syscall4_tfs( uintptr_t a, uintptr_t b, uintptr_t c, uintptr_t d, int sc );
#define _T(n)	(n + TRANSFORM)

#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


#define CLOSE(f)		((int)syscall4_tfs((uintptr_t)f,0,0,0,_T(SYS_close)))
#define FSTAT(f,s)		((int)syscall4_tfs((uintptr_t)f,(uintptr_t)s,0,0,_T(SYS_fstat64)))
#define FSTATAT(d,f,s,o)	((int)syscall4_tfs((uintptr_t)d,(uintptr_t)f,(uintptr_t)s,(uintptr_t)o,_T(SYS_fstatat64)))
#define MKDIR(p,m)		((int)syscall4_tfs((uintptr_t)p,(uintptr_t)m,(uintptr_t)0,0,_T(SYS_mkdir)))
#define READ(d,b,n) 		syscall4_tfs((uintptr_t)d,(uintptr_t)b,(uintptr_t)n,0,_T(SYS_read))
#define PREAD(d,b,n,o) 		pread(d,b,n,o)
#define WRITE(d,b,n) 		syscall4_tfs((uintptr_t)d,(uintptr_t)b,(uintptr_t)n,0,_T(SYS_write))
#define PWRITE(d,b,n,o) 	pwrite(d,b,n,o)
#define FSYNC(f) 		fsync(f)
#define FTRUNCATE(f,l)		((int)syscall4_tfs((uintptr_t)f,(uintptr_t)l,0,0,_T(SYS_ftruncate)))
#define FCNTL(f,c,v)		((int)syscall4_tfs((uintptr_t)f,(uintptr_t)c,(uintptr_t)v,0,_T(SYS_fcntl)))
#define FLOCK(f,o)		((int)syscall4_tfs((uintptr_t)f,(uintptr_t)o,0,0,_T(SYS_flock)))
#define STATFS(p,b)		((int)syscall4_tfs((uintptr_t)p,(uintptr_t)b,0,0,_T(SYS_statfs64)))

#define ACCESS_NOM		syscall4_tfs
#define ACCESS(p,m)		((int)syscall4_tfs((uintptr_t)p,(uintptr_t)m,(uintptr_t)0,(uintptr_t)0,_T(SYS_access)))
#define FACCESSAT(d,p,m,f)	((int)syscall4_tfs((uintptr_t)d,(uintptr_t)p,(uintptr_t)m,(uintptr_t)f,_T(SYS_faccessat)))

#define OPEN_NOM		syscall4_tfs
#define OPEN(p,f,m)		((int)syscall4_tfs((uintptr_t)p,(uintptr_t)f,(uintptr_t)m,(uintptr_t)0,_T(SYS_open)))
#define OPENAT_NOM		syscall4_tfs
#define OPENAT(d,p,f,m)		((int)syscall4_tfs((uintptr_t)d,(uintptr_t)p,(uintptr_t)f,(uintptr_t)m,_T(SYS_openat)))

#define UNLINK(p)		((int)syscall4_tfs((uintptr_t)p,(uintptr_t)0,0,0,_T(SYS_unlink)))
#define PIPE(a)			((int)syscall4_tfs((uintptr_t)a,(uintptr_t)0,0,0,_T(SYS_pipe)))

#include <sys/mman.h>
#define MMAP_NOM		mmap
#define MMAP(a,l,p,f,fd,o)	mmap(a,l,p,f,fd,o)
#define MUNMAP(a,l)		((int)syscall4_tfs((uintptr_t)a,(uintptr_t)l,0,0,_T(SYS_munmap)))
#define MPROTECT_NOM		syscall4_tfs
//#define MPROTECT(a,l,p)	mprotect(a,l,p)
#define MPROTECT(a,l,p)		((int)syscall4_tfs((uintptr_t)a,(uintptr_t)l,(uintptr_t)p,0,_T(SYS_mprotect)))

#include <stdlib.h>
#define MALLOC(l)		malloc(l)
#define FREE(a)			free(a)

#include <assert.h>
#define ASSERT(...)		assert(__VA_ARGS__)

#define ABORT() do { ASSERT(0); abort(); } while(0)

#include <poll.h>
#define POLL(f,n,t)		((int)syscall4_tfs((uintptr_t)f,(uintptr_t)n,(uintptr_t)t,0,_T(SYS_poll)))

#include <sys/socket.h>
#define RECV(s,b,l,f)		recv(s,b,l,f)
//#define RECV(s,b,l,f)		((size_t)syscall4_tfs((uintptr_t)s,(uintptr_t)b,(uintptr_t)l,(uintptr_t)f,_T(SYS_recv)))
#define SEND(s,b,l,f)		send(s,b,l,f)
//#define SEND(s,b,l,f)		((size_t)syscall4_tfs((uintptr_t)s,(uintptr_t)b,(uintptr_t)l,(uintptr_t)f,_T(SYS_send)))
#define SENDMSG(s,m,f)		sendmsg(s,m,f)
#define GETPEERNAME(s,a,l)	((int)syscall4_tfs((uintptr_t)s,(uintptr_t)a,(uintptr_t)l,0,_T(SYS_getpeername)))
#define SOCKET(d,t,p)		socket(d,t,p)
#define CONNECT(s,a,l)		((int)syscall4_tfs((uintptr_t)s,(uintptr_t)a,(uintptr_t)l,0,_T(SYS_connect)))
#define BIND(s,a,l)             bind(s,a,l)
#define ACCEPT(s,a,l)           accept(s,a,l)
#define SETSOCKOPT(s,o,n,v,l)   setsockopt(s,o,n,v,l)

#include <sys/syscall.h>
#define SYSCALL(n, ...)		syscall(n, __VA_ARGS__)

#define CSOPS_NOM		syscall4_tfs
#define CSOPS(a,b,c,d)		((int)syscall4_tfs((uintptr_t)a,(uintptr_t)b,(uintptr_t)c,(uintptr_t)d,_T(SYS_csops)))

#include <sys/sysctl.h>
#define SYSCTL_NOM		sysctl
#define SYSCTL(...)		sysctl(__VA_ARGS__)

#endif
