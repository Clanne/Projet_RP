#ifndef IP_HEADER__H_
#define IP_HEADER__H_

#define ICMP_NUM 1
#define TCP_NUM 6
#define UDP_NUM 17

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	uint8_t version;
	uint8_t ToS;
	uint16_t length;
	uint16_t identification ;
	uint16_t flags;
	uint8_t TTL;
	uint8_t protocol;
	uint16_t checksum;
	unsigned int source_ip;
	unsigned int dest_ip;
}ipv4_header_t;


void forge_ipv4_header( ipv4_header_t* iph , unsigned int ipsource ,  unsigned int ipdest );

void set_protocol( ipv4_header_t* iph , uint8_t protonum );

void set_TTL( ipv4_header_t* iph , int ttl );

void set_packet_length( ipv4_header_t* iph , uint16_t length );

#endif
