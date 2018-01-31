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

void* thread_send(void* ptr)
{
	char buff[MAX];
	Node* ptrc = (Node*)ptr;
	int socket=ptrc->sockfd;	
	while(fgets(buff,sizeof(buff),stdin)!=NULL)
	{
		send(socket,buff,strlen(buff),0);
	}
	close(socket); 
	pthread_exit(NULL);
}	

void* thread_read(void* ptr)
{
	char buff[MAX];
	int n;
	Node* ptrc = (Node*)ptr;
	int socket=ptrc->sockfd;	
	while(1)
	{
		memset(buff,0,sizeof(buff));
		n=read(socket,buff,MAX);
		if(n<=0)
		{
			perror("closed");
			exit(0);
		}
		else
			std::cout<< buff <<std::endl;

	}
	close(socket);
	pthread_exit(NULL);
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
	signal(SIGCHLD,SIG_IGN);//避免僵尸进程

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
	Node head;
	head.sockfd=sock_fd;

	int send_r = pthread_create(&tid[0],NULL,thread_send,&head);
	if(send_r)
	{
	   std::cout<<"pthread_create error : send_r="<< send_r<< std::endl;
	}

	int read_r = pthread_create(&tid[1],NULL,thread_read,&head);
	if(read_r)
	{
	   std::cout<<"pthread_create error : read_r="<< read_r<<std::endl;
	}
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	return 0;
}
