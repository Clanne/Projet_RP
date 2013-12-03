#include "icmp_header.h"

void forge_icmp_header( icmp_header_t* icmph ){
	
	memset( icmph , 0 , sizeof( icmp_header_t ) );
	icmph->id = ntohs( getpid() );
	//~ icmph->seqnum = 0;
}

void set_icmp_type( icmp_header_t* icmph , uint8_t type ){
	icmph->type = type;
}
