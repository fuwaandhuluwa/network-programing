#ifndef _SIG_CHLD_
#define _SIG_CHLD_

#include <iostream>
#include "network.h"
void sig_chld(int signo)
{
	pid_t pid;
	int   stat;
	//清理已终止的子进程
	while( (pid = waitpid(-1, &stat, WNOHANG)) > 0 )
 	     std::cout<<"child "<<pid <<" terminated"<<std::endl;
	return;
}


#endif
