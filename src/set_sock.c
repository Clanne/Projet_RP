#include "set_sock.h"


struct addrinfo* get_host_addr( char* hostname ){
	
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
	return result;
}
