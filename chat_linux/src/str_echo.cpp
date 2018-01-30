#include "../include/network.h"
#include "../include/Sock_rw.h"
#include <iostream>

void str_echo(int sockfd)
{
	ssize_t n;
	char buff[MAX];
	
	again:
	    while( ( n = read(sockfd, buff, MAX)) > 0)
	    {
	       writen(sockfd, buff , n); 
	    }
	    if( n < 0 && errno == EINTR)
	       goto again; 
	    if( n < 0)
	    {
	       std::cout<<"read erro : " <<strerror(errno)<<std::endl;
	       exit(-1); 
	    }	
}
