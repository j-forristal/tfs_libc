// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TIME(t)			time(t)

int atoi_tfs(const char* a,int b);
int itoa_tfs(unsigned int a,char* b);
#define ATOI(a,b)		atoi_tfs(a,b)
#define ITOA(a,b)		itoa_tfs(a,b)


#include <sys/syscall.h>
#include <stdint.h>

#include <string.h>

void* memcpy_tfs(void *dst, const void *src, size_t n);
#define TFMEMCPY(d,s,n)		memcpy_tfs(d,s,n)

void* memset_tfs( void *b, int c, size_t len);
#define MEMSET(b,c,l)		memset_tfs(b,c,l)
#define MEMSET_REF		memset_tfs

int memcmp_tfs(const void *s1, const void *s2, size_t n);
#define MEMCMP(s1,s2,n)		memcmp_tfs(s1,s2,n)

size_t strlen_tfs(const char *s);
#define STRLEN(s)		strlen_tfs(s)

char* strstr_tfs(const char *a, const char *b);
#define STRSTR(a,b)		strstr_tfs(a,b)

ssize_t syscall4_tfs( uintptr_t a, uintptr_t b, uintptr_t c, uintptr_t d, int sc );
ssize_t pio_helper_tfs( int, void *, size_t, off_t, int sc );
int	ftruncate_helper_tfs( int, off_t );

#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


// LP64 SPECIALS
#ifdef __LP64__
#define NR_FCNTL	__NR_fcntl
#define NR_FSTATAT	__NR_newfstatat
#define NR_FSTAT	__NR_fstat
#define NR_FTRUNCATE	__NR_ftruncate
#else
#define NR_FCNTL	__NR_fcntl64
#define NR_FSTATAT	__NR_fstatat64
#define NR_FSTAT	__NR_fstat64
#define NR_FTRUNCATE	__NR_ftruncate64
#endif

// OLDER ANDROID IS MISSING A FEW THINGS
#ifndef __NR_faccessat
// NOTE: LP64 will already have this defined, so we just need LP32
#ifdef __arm__
#define __NR_faccessat 334
#endif
#ifdef __i386___
#define __NR_faccessat 307
#endif
#endif

#ifndef TRANSFORM
#define TRANSFORM 23
#endif

#define _T(n)	(n + TRANSFORM)


#define CLOSE(f)		((int)syscall4_tfs((uintptr_t)f,0,0,0,_T(__NR_close)))
#define FSTAT(f,s)		((int)syscall4_tfs((uintptr_t)f,(uintptr_t)s,0,0,_T(NR_FSTAT)))
#define FSTATAT(d,f,s,o)	((int)syscall4_tfs((uintptr_t)d,(uintptr_t)f,(uintptr_t)s,(uintptr_t)o,_T(NR_FSTATAT)))
#define MKDIR(p,m)		((int)syscall4_tfs((uintptr_t)AT_FDCWD,(uintptr_t)p,(uintptr_t)m,0,_T(__NR_mkdirat)))
#define READ(d,b,n) 		syscall4_tfs((uintptr_t)d,(uintptr_t)b,(uintptr_t)n,0,_T(__NR_read))
#define PREAD(d,b,n,o) 		pio_helper_tfs(d,b,n,o,_T(__NR_pread64))
#define WRITE(d,b,n) 		syscall4_tfs((uintptr_t)d,(uintptr_t)b,(uintptr_t)n,0,_T(__NR_write))
#define PWRITE(d,b,n,o) 	pio_helper_tfs(d,b,n,o,_T(__NR_pwrite64))

#define FSYNC(f) 		((int)syscall4_tfs((uintptr_t)f,0,0,0,_T(__NR_fsync)))

#define FTRUNCATE(f,l)		ftruncate_helper_tfs(f,l)

#define FCNTL(f,c,v)		((int)syscall4_tfs((uintptr_t)f,(uintptr_t)c,(uintptr_t)v,0,_T(NR_FCNTL)))
#define FLOCK(f,o)              ((int)syscall4_tfs((uintptr_t)f,(uintptr_t)o,0,0,_T(__NR_flock)))

#ifdef __LP64__
#define STATFS(p,b)		((int)syscall4_tfs((uintptr_t)p,(uintptr_t)b,0,0,_T(__NR_statfs)))
#else
#define STATFS(p,b)		((int)syscall4_tfs((uintptr_t)p,(uintptr_t)(sizeof(*b)),(uintptr_t)b,0,_T(__NR_statfs64)))
#endif

#define ACCESS_NOM		syscall4_tfs
#define ACCESS(p,m)		((int)syscall4_tfs((uintptr_t)AT_FDCWD,(uintptr_t)p,(uintptr_t)m,(uintptr_t)0,_T(__NR_faccessat)))
#define FACCESSAT(d,p,m,f)	((int)syscall4_tfs((uintptr_t)d,(uintptr_t)p,(uintptr_t)m,(uintptr_t)f,_T(__NR_faccessat)))
#define OPEN_NOM		syscall4_tfs
#define OPEN(p,f,m)		((int)syscall4_tfs((uintptr_t)AT_FDCWD,(uintptr_t)p,(uintptr_t)f,(uintptr_t)m,_T(__NR_openat)))
#define OPENAT_NOM		syscall4_tfs
#define OPENAT(d,p,f,m)		((int)syscall4_tfs((uintptr_t)d,(uintptr_t)p,(uintptr_t)f,(uintptr_t)m,_T(__NR_openat)))
#define UNLINK(p)		((int)syscall4_tfs((uintptr_t)AT_FDCWD,(uintptr_t)p,0,0,_T(__NR_unlinkat)))
#define PIPE2(a,f)		pipe2(a,f)


#include <sys/mman.h>
//void* mmap_helper_tfs(void *a, size_t l, int p, int f, int fd, off_t o );
//#define MMAP(a,l,p,f,fd,o)	mmap_helper_tfs(a,l,p,f,fd,o)
#define MMAP_NOM		mmap
#define MMAP(a,l,p,f,fd,o)	mmap(a,l,p,f,fd,o)

#define MUNMAP(a,l)		((int)syscall4_tfs((uintptr_t)a,(uintptr_t)l,0,0,_T(__NR_munmap)))
#define MPROTECT_NOM		syscall4_tfs
#define MPROTECT(a,l,p)		((int)syscall4_tfs((uintptr_t)a,(uintptr_t)l,(uintptr_t)p,0,_T(__NR_mprotect)))

#include <stdlib.h>
#define MALLOC(l)		malloc(l)
#define FREE(a)			free(a)

#include <assert.h>
#define ASSERT(...)		assert(__VA_ARGS__)

#define ABORT() 		do { ASSERT(0); abort(); } while(1)

#include <poll.h>
#ifdef __LP64__
int poll_helper_tfs( struct pollfd *fds, unsigned fd_count, int ms );
#define POLL(f,n,t)		poll_helper_tfs(f, n, t)
#else
#define POLL(f,n,t)		((int)syscall4_tfs((uintptr_t)f,(uintptr_t)n,(uintptr_t)t,0,_T(__NR_poll)))
#endif

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

#if 0
#include <sys/sysctl.h>
#define SYSCTL(...)             sysctl(__VA_ARGS__)
#endif


// NOTE: inotify is not on all platforms; we can include
// defines here that may never be used, as long as they
// don't have tendrils to headers, etc.  Caller must
// include inotify.h
#define INOTIFY_INIT()          ((int)syscall4_tfs(0,0,0,0,_T(__NR_inotify_init1)))
#define INOTIFY_ADD_WATCH(f,p,m)        ((int)syscall4_tfs((uintptr_t)f,(uintptr_t)p,(uintptr_t)m,0,_T(__NR_inotify_add_watch)))


// Linux particular tee()/splice()/vmsplice() support
#define SPLICE(a,b,c,d,e,f)		splice(a,b,c,d,e,f)
#define VMSPLICE(a,b,c,d)		vmsplice(a,b,c,d)
#define TEE(a,b,c,d)			tee(a,b,c,d)




#ifdef __cplusplus
}
#endif

#endif
