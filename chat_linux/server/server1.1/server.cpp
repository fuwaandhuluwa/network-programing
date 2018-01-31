#include "../../include/network.h"
#include "../../include/Sock_ntop.h"
#include "../../include/str_echo.h"
#include <iostream>
#include "../../include/sig_chld.h"

#define LISTENQ 5 

int main(int argc, char **argv)
{

  if(argc <= 1)
	std::cout<< "pleace input the server port ..." << std::endl;
  else{
	std::cout << "server port is " << argv[1] << std::endl;
  }
  
  pid_t pid;
  int listenfd, connfd;
  struct sockaddr_in seraddr;
  socklen_t len;
  struct sockaddr_in cliaddr;

  if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) 
  {
	std::cout << "socket error : " << strerror(errno) << std::endl;
	return(-1);
  }
  bzero(&seraddr, sizeof(seraddr));
  
  seraddr.sin_family = AF_INET;
  seraddr.sin_port = htons(atoi(argv[1]));
  seraddr.sin_addr.s_addr = htonl(INADDR_ANY);  

  if ( (bind(listenfd, (SA*)&seraddr, sizeof(seraddr))) < 0 )
  {
	std::cout << "bind error : " << strerror(errno) << std::endl;
	return(-1);
  } 
  if( (listen( listenfd , LISTENQ)) < 0) 
  {
	std::cout << "listen error : " << strerror(errno) << std::endl;
	return(-1);
  }
  signal(SIGCHLD,sig_chld); 
  while(1)
  {
	len = sizeof(cliaddr);
	char buf[1024];
        if( (connfd = accept(listenfd, (SA*)&cliaddr, &len)) < 0 ) 
	{
	   std::cout << "accept error : " << strerror(errno) << std::endl;
	   return(-1);
	}
	if( (pid = fork()) == 0)
	{
	   close(listenfd);
	   std::cout<<"child process is running..." <<std::endl;
  	   std::cout << "connect from IP : " << inet_ntop(AF_INET,&cliaddr.sin_addr,buf,sizeof(buf))<<" : "<< ntohs(cliaddr.sin_port) << std::endl;
	   str_echo(connfd);	   
	   close(connfd);
	   exit(0);
  	}	
	close(connfd);
  }
  close(listenfd);
}
