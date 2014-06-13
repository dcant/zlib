/*************************************************************************
    > File Name: zsignal.h
    > Author: zang
    > Mail: zangzhida@gmail.com 
    > Created Time: Thu 12 Jun 2014 01:47:22 PM CST
 ************************************************************************/

#ifndef _ZSIGNAL_H_
#define _ZSIGNAL_H_

#include "zerror.h"
#include <signal.h>

/****************************
 * signal related functions *
 ****************************/
typedef void (*sighandler_t)(int);

void zsigprocmask(int how, const sigset_t *set, sigset_t *oldset)
{
	if (sigprocmask(how, set, oldset) < 0)
		zerror("sigprocmask error!");
}

void zsigemptyset(sigset_t *set)
{
	if (sigemptyset(set) < 0)
		zerror("sigemptyset error!");
}

void zsigfillset(sigset_t *set)
{
	if (sigfillset(set) < 0)
		zerror("sigfillset error!");
}

void zsigaddset(sigset_t *set, int signum)
{
	if (sigaddset(set, signum) < 0)
		zerror("sigaddset error!");
}

void zsigdelset(sigset_t *set, int signum)
{
	if (sigdelset(set, signum) < 0)
		zerror("sigdelset error!");
}

int zsigismember(const sigset_t *set, int signum)
{
	int r;
	if ((r = sigismember(set, signum)) < 0)
		zerror("sigismember error!");
	return r;
}

sighandler_t zsignal(int signum, sighandler_t handler)
{
	struct sigaction action;
	struct sigaction oldaction;

	action.sa_handler = handler;
	zsigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;

	if (sigaction(signum, &action, &oldaction) < 0)
		zerror("signal error!");

	return oldaction.sa_handler;
}

#endif
