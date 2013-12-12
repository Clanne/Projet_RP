#ifndef PING__H_
#define PING__H_

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
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

void (*forge_ip_header)(void*, struct sockaddr*  , uint8_t);
int protonum = IPPROTO_ICMP;
int addr_family = AF_INET;
socklen_t addrlen = sizeof( struct sockaddr_in );
int headeroffset = sizeof( ipv4_header_t );


int icmp_ping( void* pack  , struct sockaddr* dest_addr , int sockfd , timer_stats* ts);

int read_package( void* rcvpack );

void forge_icmp_ping( void* buf , struct sockaddr* dest_addr );

void ping_loop(struct sockaddr* dest_addr );

#endif
