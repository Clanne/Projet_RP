#include "ping.h"

package_t* forge_ping_pack( unsigned int source_addr ,  unsigned int dest_addr ){
	package_t* ping = malloc( sizeof( package_t ) );
	
	forge_ipv4_header( &ping->ipv4h , source_addr , dest_addr );
	set_TTL( &ping->ipv4h , 30 );
	set_packet_length( &ping->ipv4h , sizeof( package_t ) );
	set_protocol( &ping->ipv4h , ICMP_NUM );
	
	forge_icmp_header( &ping->icmph );
	set_icmp_type( &ping->icmph , ECHO_REQUEST );
	return ping;
}

void ping_loop(char* hostname , package_t* pack){
	
	char str[10];
	timer t;
	int sockfd = socket( PF_INET , SOCK_RAW , IPPROTO_ICMP );
	int packreceived ;
	
	fd_set sock;
	FD_ZERO( &sock );
	FD_SET(sockfd , &sock);
	
	struct timeval timeout;
	struct addrinfo *result , hints;
	
	memset (&hints, 0, sizeof (struct addrinfo));
	hints.ai_family		= AF_INET;
	hints.ai_socktype	= SOCK_RAW;
	hints.ai_flags		= 0;
	hints.ai_protocol	= IPPROTO_ICMP;
	
	if (getaddrinfo (hostname, "80", &hints , &result) != 0) {
		perror ("Client error (getaddrinfo)");
		exit (EXIT_FAILURE);
	}
	
	struct sockaddr_in* dest = (struct sockaddr_in*)result->ai_addr ;
	pack->ipv4h.dest_ip = dest->sin_addr.s_addr ;
	
	int i;
	for (i = 0; i < 5 ; i++)
	{
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		
		sendto( sockfd , (void*)pack ,sizeof( package_t ) , 0 , result->ai_addr ,  result->ai_addrlen );
		
		starttimer( &t ); 
		packreceived = select( 1 , &sock , NULL , NULL , &timeout );
		stoptimer( &t );
		sprint_timervalue( &t , str );
		if(packreceived)
			printf("package received in %s\n",str);
		else printf("fail\n");
	}
		
}

int main( int argc , char* argv[] ){
	
	package_t* pack = forge_ping_pack( 0 , 0 );
	ping_loop( argv[1] , pack );
	exit(0);
	
}
