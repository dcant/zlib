/*************************************************************************
    > File Name: zprocess.h
    > Author: zang
    > Mail: zangzhida@gmail.com 
    > Created Time: Thu 12 Jun 2014 01:22:38 PM CST
 ************************************************************************/

#ifndef _ZPROCESS_H_
#define _ZPROCESS_H_

#include "zerror.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/*****************************
 * process related functions *
 *****************************/
pid_t zfork()
{
	pid_t pid;
	if ((pid = fork()) < 0)
		znerror("fork error!");
	return pid;
}

pid_t zgetpid()
{
	//getpid is always successful.
	return getpid();
}

pid_t zgetppid()
{
	//getppid is always successful.
	return getppid();
}

pid_t zgetpgrp()
{
	//returns the PGID of the calling process.
	return getpgrp();
}

void zsetpgid(pid_t pid, pid_t pgid)
{
	if (setpgid(pid, pgid) < 0)
		znerror("setpgid error!");
}

pid_t zwait(int *status)
{
	pid_t pid;
	if ((pid = wait(status)) < 0)
		zerror("wait error!");
	return pid;
}

pid_t zwaitpid(pid_t pid, int *status, int options)
{
	pid_t tpid;
	if ((tpid = waitpid(pid, status, options)) < 0)
		zerror("waitpid error!");
	return tpid;
}

unsigned int zsleep(unsigned int secs)
{
	return sleep(secs);
}

void zexecve(const char *filename, char *const argv[], char *const envp[])
{
	if (execve(filename, argv, envp) < 0)
		znerror("execve error!");
}

void zkill(pid_t pid, int sig)
{
	if (kill(pid, sig) < 0)
		znerror("kill error!");
}

void zpause()
{
	if (pause() < 0)
		znerror("pause error!");
}

unsigned int zalarm(unsigned int seconds)
{
	return alarm(seconds);
}

#endif
