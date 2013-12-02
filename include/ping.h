#ifndef PING__H_
#define PING__H_

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include "set_sock.h"
#include "icmp_header.h"
#include "ip_header.h"
#include "timer.h"

typedef struct{
	ipv4_header_t ipv4h ;
	icmp_header_t icmph ;
} package_t ;

char* gethostip();

package_t* forge_ping_pack(  );

unsigned short cksum(uint16_t *addr, int len);

void ping_loop(struct sockaddr* dest_addr , package_t* pack);

#endif
