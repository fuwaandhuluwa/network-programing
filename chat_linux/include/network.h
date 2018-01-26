/* header file */
#ifndef _HEADER_H_
#define _HEADER_H_


#include <netinet/in.h>      /*IPv4---sockaddr_in IPv6--sockaddr_in6*/
#include <sys/socket.h>      /*sockaddr*/ 
#include <arpa/inet.h>       /*inet_pton   inet_ntop*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>       /*sszie_t...*/
#include <unistd.h>          /*fork*/
#include <sys/errno.h>       /*errno*/
#include <stdlib.h>          /*atoi*/


typedef struct sockaddr SA;

#endif
