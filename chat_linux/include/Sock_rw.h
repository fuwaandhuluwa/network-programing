#ifndef SOCK_WR_
#define SOCK_WR_


#include "network.h"

ssize_t readn(int filedes, void * buff, size_t nbytes);

ssize_t writen(int filedes, const void * buff, size_t nbytes);

ssize_t readline(int filedes, void * buff, size_t maxlen);





#endif
