#ifndef PING__H_
#define PING__H_

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include "icmp_header.h"
#include "ip_header.h"
#include "timer.h"

typedef struct{
	ipv4_header_t ipv4h ;
	icmp_header_t icmph ;
} package_t ;

package_t* forge_ping_pack( unsigned int source_addr ,  unsigned int dest_addr );

void ping_loop(char* hostname , package_t* pack);

#endif
