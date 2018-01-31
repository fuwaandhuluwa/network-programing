#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <error.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <signal.h>
#include "../../include/Node.h"
#include "../../include/network.h"

#define MAX 1024
#define max(x,y) ((x)>(y)?(x):(y))

void str_cli(FILE *fp, int sockfd)
{
	int maxfdp1, stdieof;
	fd_set rset;
	char buff[MAX];
	int n;

	stdieof = 0;
	FD_ZERO(&rset);
	for(;;)
	{
	   if(stdieof == 0)	
		FD_SET(fileno(fp), &rset);
	   FD_SET(sockfd, &rset);
	   maxfdp1 = max(fileno(fp), sockfd) +1;
	   select(maxfdp1, &rset, NULL, NULL, NULL);

	   if(FD_ISSET(sockfd, &rset))
	   {
		if( (n = read(sockfd, buff, MAX)) == 0)
		{
		   if( stdieof == 1)
			return;
		    else
		   {
			std::cout<< "str_cli: server terminated prematurely"<<std::endl;
			exit(0);
	    	   }	
		}
		  write(fileno(stdout), buff, n);
	   }
	   if(FD_ISSET(fileno(fp), &rset))
	   {
		if( (n = read(fileno(fp),  buff,MAX)) == 0)
		{ 
		   stdieof = 1;
		   shutdown(sockfd, SHUT_WR);
		   FD_CLR(fileno(fp), &rset);
		   continue;
		}
		write(sockfd,buff,n);
	   }
	}
}

int main(int argc,char **argv)
{
        if(argc <= 1)
	    std::cout << "pleace input the server IP and port..." << std::endl;
        else
	{
	    std::cout << "server IP is "<<argv[1] <<std::endl;
	    std::cout << "server port is "<<argv[2] <<std::endl;
	}
	struct sockaddr_in servaddr;
	int sock_fd;
	pthread_t tid[2];

	signal(SIGPIPE,SIG_IGN);//设置进程不会被系统自动关闭
	signal(SIGCHLD,SIG_IGN);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(atoi(argv[2]));
	
  	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) 
	   std::cout<<"inet_pton error for "<< argv[1] << std::endl;

	if( (sock_fd=socket(AF_INET,SOCK_STREAM,0)) < 0 )
	   std::cout<< "socket error"<< std::endl;

	if(connect(sock_fd,(SA*) &servaddr,sizeof(servaddr)) < 0)
	{
	   std::cout<< "connect error"<< std::endl;
	   return(-1);
	}
	std::cout<<"connect success ..." <<std::endl;

	str_cli(stdin,sock_fd);
	close(sock_fd);
	return 0;
}
