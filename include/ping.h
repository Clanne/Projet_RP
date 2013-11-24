#ifndef PING__H_
#define PING__H_

#include <sys/types.h>
#include <sys/socket.h>
#include "icmp_header.h"

typedef struct{
	ipv4_header_t ipv4h ;
	icmp_header_t icmph ;
} package_t ;

package_t* forge_ping_pack( unsigned int source_addr ,  unsigned int dest_addr );

#endif
