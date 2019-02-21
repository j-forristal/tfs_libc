// TFS_LIB
// Written 2019 by Jeff Forristal, jeff@forristal.com
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty. Please see CC0 Public Domain Dedication.

#include <errno.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/poll.h>
#include <time.h>

#ifndef TRANSFORM
#define TRANSFORM 23
#endif

// Source code from http://androidxref.com/6.0.1_r10/xref/bionic/libc/bionic/__set_errno.cpp
long __set_errno_internal_tfs(int n) {
	errno = n;
	return -1;
}

ssize_t pread_tfs(int,void*,size_t,off64_t);
ssize_t pwrite_tfs(int,void*,size_t,off64_t);
ssize_t pio_helper_tfs(int fd, void *buf, size_t nbyte, off_t offset, int sc)
{
	// 32-bit systems use off_t, but the syscall is off64_t; we we have to
	// widen.  Ref: http://androidxref.com/6.0.1_r10/xref/bionic/libc/bionic/legacy_32_bit_support.cpp
	off64_t off = (off64_t)offset;
	if( sc == (__NR_pread64 + TRANSFORM) ) return pread_tfs(fd, buf, nbyte, off);
	return pwrite_tfs(fd, buf, nbyte, off);
}

#define MMAP2_SHIFT 12
void* mmap_tfs(void *a, size_t s, int p, int f, int fd, off64_t o );
void* mmap_helper_tfs(void *a, size_t s, int p, int f, int fd, off_t o )
{
	// 32-bit systems need translation of the offset parameter
#ifdef __LP64__
	return mmap_tfs(a,s,p,f,fd,o);
#else
	off64_t off = (off64_t)o;
	if( (off & ((1UL << MMAP2_SHIFT)-1)) != 0 ){
		errno = EINVAL;
		return MAP_FAILED;
	}
	return mmap_tfs(a,s,p,f,fd,(off >> MMAP2_SHIFT));
#endif
}

int ppoll_tfs(struct pollfd*, unsigned int, struct timespec*, const void*, size_t);
int poll_helper_tfs( struct pollfd *fds, unsigned fd_count, int ms )
{
	struct timespec ts;
	struct timespec *ts_ptr = NULL;
	if( ms > 0 ){
		ts.tv_sec = ms / 1000;
		ts.tv_nsec = (ms % 1000) * 1000000;
		ts_ptr = &ts;
	}
	return ppoll_tfs(fds, fd_count, ts_ptr, NULL, 0);
}

int ftruncate_tfs(int,off64_t);
int ftruncate_helper_tfs(int fd, off_t o)
{
	// 32-bit systems need translation of the offset parameter
#ifdef __LP64__
	return ftruncate_tfs(fd, o);
#else
	off64_t off = (off64_t)o;
	return ftruncate_tfs(fd, off);
#endif
}
