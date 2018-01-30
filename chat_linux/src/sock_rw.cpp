#include "../include/Sock_rw.h"
#include "../include/network.h"

ssize_t readn(int fd, void * buff, size_t nbytes)
{
	size_t nleft; 
	ssize_t nread;
	char * ptr;	
	ptr =(char *) buff;
	nleft = nbytes;
	while(nleft > 0)
	{
	    if( (nread = read(fd, ptr, nleft)) < 0)	
	    {
		if(errno == EINTR)
		{
		   nread = 0;
		}
		else{
		   return(-1);	
		}
	    }
	    else if (nread == 0){
		break;	
            }
	    nleft -= nread;	
	    ptr += nread;
	}
	return(nbytes - nleft);
}


ssize_t writen(int fd, const void * buff, size_t n)
{
	size_t nleft; 
	size_t nwriten;	
	const char * ptr;

	ptr = (char *)buff;
	nleft = n;
	while(nleft > 0)
	{
 	   if ( (nwriten = write(fd, ptr, nleft)) < 0)	
	    {
		if( errno== EINTR)	
		    nwriten = 0;
		else
		    return(-1);
	    }else if( nwriten == 0)	
	    {
		break;
	    }
	    nleft -= nwriten;
	    ptr += nwriten;
	}
	return(n - nleft);
}

ssize_t readline(int fd, void * buff, size_t maxlen)
{
	ssize_t n, rc;
	char c, *ptr;
	
	ptr = (char *)buff;
	for( n = 1; n < maxlen; n++)
	{
	  again:	
	      if ( ( rc = read(fd,&c,1)) ==1)
		{
		   *ptr++ = c; 
		   if ( c == '\n')
			break;
		}else if (rc == 0 )
		{
		   *ptr = 0;	
		   return(n - 1);
		}
		else{
		   if(errno == EINTR)	
		    {
		      goto again; 
		    }	
		    return(-1);
		}
	}
	*ptr = 0;
	return(n);
}
