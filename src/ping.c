#include "ping.h"

package_t* forge_ping_pack( unsigned int source_addr ,  unsigned int dest_addr ){
	package_t* ping = malloc( sizeof( package_t ) );
	
	forge_ipv4_header( &ping->ipv4h , source_addr , dest_addr );
	set_TTL( &ping->ipv4h , 30 );
	set_packet_length( &ping->ipv4h , sizeof( package_t ) );
	set_protocol( &ping->ipv4h , ICMP_NUM );
	
	forge_icmp_header( &ping->icmph );
	set_icmp_type( &ping->icmph , ECHO_REQUEST );
}

void ping_loop(unsigned int dest_addr){
	
	int sockfd = socket( PF_INET , SOCK_RAW , IPPROTO_ICMP );
	
	
}
