#include "../include/Sock_ntop.h"

namespace NETWORK{

   char*
   sock_ntop(const struct sockaddr *sock_addr, socklen_t addrlen)
   {
      char portstr[8];
      static char str[128];
      switch(sock_addr->sa_family) {
         case AF_INET:{
            struct sockaddr_in *sin= (struct sockaddr_in*)sock_addr;
	    if(inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL){
		 return(NULL);
               }
	    if( ntohs(sin->sin_port) != 0){
		 snprintf(portstr, sizeof(portstr), ":%d",ntohs(sin->sin_port));
	         strcat(str, portstr);	
             }
	    return(str);
	  }
	 case AF_INET6:{
             struct sockaddr_in6* sin=(struct sockaddr_in6*)sock_addr;
 	     if(inet_ntop(AF_INET6, &sin->sin6_addr, str, sizeof(str)) == NULL){
	    	  return(NULL);	
		}
	     if(ntohs(sin->sin6_port) != 0) 
		{
		snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin->sin6_port));
	        strcat(str, portstr); 
		}
		return(str);
	  }
      }
   }
}

