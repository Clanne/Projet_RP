#include "set_sock.h"


int create_raw_socket( int addr_family , int proto ){
	
	int sockfd , on;
	
	if( ( sockfd = socket( addr_family , SOCK_RAW , proto ) ) == -1 ){
		perror( "socket creation failed\n" );
		exit( EXIT_FAILURE );
	}
	
	if(setsockopt( sockfd , IPPROTO_IP, IP_HDRINCL, &on, sizeof(on) ) < 0)
    {
        perror("setsockopt() error");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

void get_host_addr( char* hostname , struct sockaddr* dest ){
	
	struct addrinfo *result , hints;
	
	memset (&hints, 0, sizeof (struct addrinfo));
	hints.ai_family		= AF_INET;
	hints.ai_socktype	= SOCK_RAW;
	hints.ai_flags		= 0;
	hints.ai_protocol	= IPPROTO_ICMP;
	
	if (getaddrinfo (hostname, NULL , &hints , &result) != 0) {
		perror ("error (getaddrinfo)");
		exit (EXIT_FAILURE);
	}
	
	*dest = (struct sockaddr)*result->ai_addr;
	freeaddrinfo( result );
}
