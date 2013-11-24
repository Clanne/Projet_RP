#include "set_sock.h"


void connect_socket_to_host( int sockfd , int proto , int socktype , char* hostname ){
	
	// set name resolution parameters
	memset (&hints, 0, sizeof (struct addrinfo));
	hints.ai_family		= AF_UNSPEC;
	hints.ai_socktype	= socktype;
	hints.ai_flags		= 0;
	hints.ai_protocol	= proto;

	// get remote addr from name
	if (getaddrinfo (argv[1], "5666", &hints, &result) != 0) {
		perror ("Client error (getaddrinfo)");
		exit (EXIT_FAILURE);
	}

	//si proto = tcp alors se connecter au serveur
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		if ((sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1)
			continue;
		if (proto == IPPROTO_TCP && connect (sockfd, rp->ai_addr, rp->ai_addrlen) != -1)
			break;
		close (sockfd);
	}

	
}
