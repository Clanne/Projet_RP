#include "set_sock.h"


void get_host_addr( char* hostname , struct sockaddr* dest ){
	
	struct addrinfo *result , hints;
	
	memset (&hints, 0, sizeof (struct addrinfo));
	hints.ai_family		= AF_INET;
	hints.ai_socktype	= 0;
	hints.ai_flags		= 0;
	hints.ai_protocol	= 0;
	
	if (getaddrinfo (hostname, "80", &hints , &result) != 0) {
		perror ("Client error (getaddrinfo)");
		exit (EXIT_FAILURE);
	}
	
	*dest = (struct sockaddr)(*result->ai_addr) ;
}
