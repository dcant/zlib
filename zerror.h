/*************************************************************************
    > File Name: zerror.h
    > Author: zang
    > Mail: zangzhida@gmail.com 
    > Created Time: Thu 12 Jun 2014 01:01:19 PM CST
 ************************************************************************/

#ifndef _ZERROR_H_
#define _ZERROR_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/**********************************
 * normal error handling function *
 **********************************/
void zerror(char *msg)
{
	fprintf(stderr, "[ERROR] %s\n", msg);
	exit(0);
}

/*************************************
 * handling errors with setted errno *
 *************************************/
void znerror(char *msg)
{
	fprintf(stderr, "[ERROR] %s: %s\n", msg, strerror(errno));
	exit(0);
}

#endif
