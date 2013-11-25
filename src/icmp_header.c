#include "icmp_header.h"

void forge_icmp_header( icmp_header_t* icmph ){
	//~ icmp_header_t icmph = malloc ( sizeof( icmp_header_t ) );
	memset( icmph , 0 , sizeof( icmp_header_t ) );
}

void set_icmp_type( icmp_header_t* icmph , uint8_t type ){
	icmph->type = htons(type) ;
}
