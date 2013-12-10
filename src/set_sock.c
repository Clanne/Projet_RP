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

void get_host_addr( char* hostname , struct sockaddr* dest , unsigned int ip_type , unsigned int protonum){
	
	struct addrinfo *result , hints;
	
	memset (&hints, 0, sizeof (struct addrinfo));
	hints.ai_family		= ip_type;
	hints.ai_socktype	= SOCK_RAW;
	hints.ai_flags		= 0;
	hints.ai_protocol	= protonum;
	
	if (getaddrinfo (hostname, NULL , &hints , &result) != 0) {
		perror ("error getaddrinfo");
		exit (EXIT_FAILURE);
	}
	
	if( ip_type == AF_INET )
		*dest = (struct sockaddr)*result->ai_addr;
	else{
		struct sockaddr_in6* ipv6dest = (struct sockaddr_in6*)result->ai_addr;
		*(struct sockaddr_in6*)dest  = (*ipv6dest);
	}
	freeaddrinfo( result );
}
