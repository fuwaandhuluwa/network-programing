/* sock_ntop  sock_pton*/
/* 协议无关的地址转换函数 */ 

#ifndef _SOCK_PTON_
#define _SOCK_PTON_


#include "network.h" 

namespace NETWORK
{
    char* sock_ntop(const struct sockaddr *sockaddr, socklen_t addrlen);
} 

#endif
