#include "ip_header.h"

void forge_ipv4_header( void* buf , struct sockaddr* destination , uint8_t protonum ){
	ipv4_header_t* iph = (ipv4_header_t*) buf; 
	memset( buf , 0 , sizeof( ipv4_header_t ) );	
	iph->version = 4;
	iph->IHL= 5;
	set_destination( iph ,(struct sockaddr_in *) destination );
	set_source( iph , inet_addr(SOURCEIP) );
	set_TTL(iph, 80);
	set_protocol( iph, protonum );
	set_packet_length( iph , 28 );//taille d'un echo request
	set_ipv4_checksum( iph );
}

void set_destination( ipv4_header_t* iph , struct sockaddr_in* ipdest){
	iph->dest_ip  = ipdest->sin_addr.s_addr ;
}

void set_source( ipv4_header_t* iph , unsigned int ipsource ){
	iph->source_ip = ipsource ;
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


void set_ipv4_checksum( void* buf ){
	ipv4_header_t* iph = (ipv4_header_t*) buf;
	iph->checksum = 0;
	iph->checksum = checksum( iph , 10 );
}

void forge_ipv6_header( void* buf , struct sockaddr* destination , uint8_t proto ){
	ipv6_header_t* iph = (ipv6_header_t*) buf;
	memset( iph , 0 , sizeof( ipv6_header_t ) );
	iph->version = 6;
	iph->next_header = proto;
	ipv6_set_hop_limit( buf , 80 );
}

void ipv6_set_hop_limit( ipv6_header_t* buf, uint16_t hop_limit ){
	buf->hop_limit = htons( hop_limit );
}

void ipv6_set_destination( ipv6_header_t* buf , struct sockaddr_in6 * dest ){
	uint128_t* addr  = (uint128_t*) (dest->sin6_addr.s6_addr);
	buf->dest_ip.first = addr->first;
	buf->dest_ip.second = addr->second;
}

void ipv6_set_source( ipv6_header_t* buf ){	
	inet_pton(AF_INET6, SOURCEIP6 , &(buf->source_ip) );
}
