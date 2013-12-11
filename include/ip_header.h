#ifndef IP_HEADER__H_
#define IP_HEADER__H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "checksum.h"

#define SOURCEIP "192.168.1.12"
#define SOURCEIP6 "fe80::216:e3ff:feaf:815d"

typedef struct{
	uint64_t first;
	uint64_t second;
} uint128_t ;

typedef struct{
	uint8_t IHL : 4;
	uint8_t version : 4;
	uint8_t ToS;
	uint16_t length;
	uint16_t identification ;
	uint16_t flags_offset;
	uint8_t TTL;
	uint8_t protocol;
	uint16_t checksum;
	unsigned int source_ip;
	unsigned int dest_ip;
}ipv4_header_t;

typedef struct{
	unsigned int flow_label : 20 ;
	unsigned int traffic_class : 8;
	unsigned int version : 4;
	uint16_t length;
	uint8_t next_header;
	uint8_t hop_limit;
	uint128_t source_ip;
	uint128_t dest_ip;
}ipv6_header_t ;

void forge_ipv4_header( void* buf , struct sockaddr* destination , uint8_t protonum);

void set_destination( ipv4_header_t* iph , struct sockaddr_in* ipdest);

void set_source( ipv4_header_t* iph , unsigned int ipsource );

void set_protocol( ipv4_header_t* iph , uint8_t protonum );

void set_TTL( ipv4_header_t* iph , uint8_t ttl );

void set_packet_length( ipv4_header_t* iph , uint16_t length );

void set_ipv4_checksum( void* buf );

void forge_ipv6_header( void* buf , struct sockaddr* destination , uint8_t proto );

void ipv6_set_hop_limit( ipv6_header_t* buf, uint16_t hop_limit );

void ipv6_set_destination( ipv6_header_t* buf , struct sockaddr_in6 * dest );

void ipv6_set_source( ipv6_header_t* buf );

#endif
