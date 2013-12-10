#include "icmp_header.h"

void forge_icmp_header( void* buf ){
	
	icmp_header_t* icmph = (icmp_header_t*) buf;
	memset( buf , 0 , sizeof( icmp_header_t ) );
	icmph->id = ntohs( getpid() );
}

void set_icmp_type( void* buf , uint8_t type ){
	icmp_header_t* icmph = (icmp_header_t*) buf;
	icmph->type = type;
}

void setseqnum( void* buf , uint16_t seqnum ){
	icmp_header_t* icmph = (icmp_header_t*) buf;
	icmph->seqnum = htons( seqnum );
}

void set_checksum_icmp( void* buf ){
	icmp_header_t* icmph = (icmp_header_t*) buf;
	icmph->checksum = 0;
	icmph->checksum = checksum( icmph , sizeof( icmp_header_t ) >> 1 );
}
