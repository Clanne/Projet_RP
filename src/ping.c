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

void ping_loop(struct sockaddr* dest_addr , package_t* pack){
	
	char str[10];
	timer t;
	int sockfd = socket( PF_INET , SOCK_RAW , IPPROTO_ICMP );
	int packreceived ;
	
	fd_set sock;
	FD_ZERO( &sock );
	FD_SET(sockfd , &sock);
	
	struct timeval timeout;
	
	
	struct sockaddr_in* ipv4_dest_addr = (struct sockaddr_in* ) dest_addr ;
	pack->ipv4h.dest_ip = ipv4_dest_addr->sin_addr.s_addr ;
	
	char* dest_ad;
	dest_ad = inet_ntoa( ipv4_dest_addr->sin_addr );
	printf("%s\n" , dest_ad );
	
	pack->ipv4h.source_ip = inet_addr("109.217.245.73");

	int i;
	for (i = 0; i < 5 ; i++)
	{
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		
		sendto( sockfd , (void*)pack ,sizeof( package_t ) , 0 , dest_addr ,  sizeof( struct sockaddr_in ) );
		
		starttimer( &t ); 
		packreceived = select( 1 , &sock , NULL , NULL , &timeout );
		stoptimer( &t );
		sprint_timervalue( &t , str );
		if(packreceived > 0)
			printf("package received in %s\n",str);
		else printf("fail\n");
	}
		
}

int main( int argc , char* argv[] ){
	
	package_t* pack = forge_ping_pack( 0 , 0 );
	
	struct sockaddr* dest_addr = malloc( sizeof (struct sockaddr_in) ) ;
	
	get_host_addr( argv[1] , dest_addr );
	
	ping_loop( dest_addr , pack );
	exit(0);
	
}
