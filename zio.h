/*************************************************************************
    > File Name: zio.h
    > Author: zang
    > Mail: zangzhida@gmail.com 
    > Created Time: Thu 12 Jun 2014 01:54:23 PM CST
 ************************************************************************/

#ifndef _ZIO_H_
#define _ZIO_H_

#include "zerror.h"
#include <unistd.h>

#define ZMAXBUF 8192

typedef struct {
	int zfd;
	int zub;
	char *zbp;
	char zbuf[ZMAXBUF];
} zio_t;

ssize_t zwrite(int fd, const void *buf, size_t n)
{
	size_t remain;
	size_t written;
	char *p = buf;

	while (remain > 0) {
		if ((written = write(fd, p, remain)) <= 0) {
			if (EINTR == errno)
				written = 0;
			else
				znerror("write error!");
		}

		remain -= written;
		p += written;
	}

	return n;
}

ssize_t zread(int fd, void *buf, size_t n)
{
	size_t remain;
	size_t readn;
	char *p = buf;

	while (remain > 0) {
		if ((readn = read(fd, p, remain)) <= 0) {
			if (EINTR == errno)
				readn = 0;
			else
				znerror("read error!");
		} else if (0 == readn)
			break;

		remain -= readn;
		p += readn;
	}

	return (n - remain);
}

#endif
