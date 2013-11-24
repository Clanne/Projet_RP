#include "set_sock.h"


struct addrinfo* get_host_addr( char* hostname ){
	
	struct addrinfo *result ;
	
	//~ memset (&hints, 0, sizeof (struct addrinfo));
	//~ hints.ai_family		= AF_INET;
	//~ hints.ai_socktype	= SOCK_RAW;
	//~ hints.ai_flags		= 0;
	//~ hints.ai_protocol	= IPPROTO_ICMP;
	
	if (getaddrinfo (hostname, "80", NULL , &result) != 0) {
		perror ("Client error (getaddrinfo)");
		exit (EXIT_FAILURE);
	}
	return result;
}
