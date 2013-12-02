#include "ip_header.h"

void forge_ipv4_header( ipv4_header_t* iph  ){
	
	memset( iph , 0 , sizeof( ipv4_header_t ) );	
	iph->version += 4 << 4;
	iph->version += 5;
}


void set_protocol( ipv4_header_t* iph , uint8_t protonum ){
	iph->protocol = protonum ;
}

void set_TTL( ipv4_header_t* iph , uint8_t ttl ){
	iph->TTL = ttl ;
}

void set_packet_length( ipv4_header_t* iph , uint16_t length ){
	iph->length = htons(length) ;
}
