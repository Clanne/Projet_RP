#ifndef ICMP_HEADER__H_
#define ICMP_HEADER__H_

#define ECHO_REPLY 0
#define ECHO_REQUEST 8

#include <stdio.h>
#include <stdint.h>
#include <unistd.h> 
#include <string.h>
#include <arpa/inet.h>
#include "checksum.h"
#include "ip_header.h"

typedef struct{
	uint8_t type ;
	uint8_t code ;
	uint16_t checksum ;
	uint16_t id ;
	uint16_t seqnum ;
	//~ int data;
} icmp_header_t ;

void forge_icmp_header( void* buf );

void set_icmp_type( void* buf , uint8_t type );

void setseqnum( void* buf , uint16_t seqnum );

void set_checksum_icmp( void* buf );

#endif
