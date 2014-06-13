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
#include <string.h>

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

void zbinit(zio_t *zp, int fd)
{
	zp->zfd = fd;
	zp->zub = 0;
	zp->zbp = zp->zbuf;
}

static ssize_t _zread(zio_t *zp, char *buf, size_t n)
{
	int rn;

	while (zp->zub <= 0) {
		zp->zub = read(zp->zfd, zp->zbuf, sizeof(zp->buf));

		if (zp->zub < 0) {
			if (errno != EINTR)
				znerror("_zread error!");
		} else if (0 == zp->zub)
			return 0;
		else
			zp->zbp = zp->zbuf;
	}

	rn = n;
	if (zp->zub < n)
		rn = zp->zub;

	memcpy(buf, zp->zbp, rn);
	zp->zbp += rn;
	zp->zub -= rn;

	return rn;
}

ssize_t zbreadline(zio_t *zp, void *buf, size_t maxlen)
{
	int n, r;
	char c, *bp = buf;

	for (n = 1; n < maxlen; n++) {
		if (1 == (r = _zread(zp, &c, 1))) {
			*bp++ = c;
			if ('\n' == c)
				break;
		} else if (0 == r) {
			if (1 ==n)
				return 0;
			else
				break;
		} else
			zerror("zbreadline error!");
	}

	*bp = 0;

	return n;
}

ssize_t zbread(zio_t *zp, void *buf, size_t n)
{
	size_t remain = n;
	size_t r;
	char *bp = buf;

	while (remain > 0) {
		if ((r = _zread(zp, bp, remain)) < 0) {
			if (EINTR == errno)
				r = 0;
			else
				znerror("zbread error!");
		} else if (0 == r)
			break;

		remain -= r;
		bp += r;
	}

	return (n - remain);
}

#endif
