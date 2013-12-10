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

void (*forge_ip_header)(void*, struct sockaddr* , uint8_t);
int stop = 0;
int protonum = IPPROTO_ICMP;
int addr_family = AF_INET;
int headeroffset = sizeof( ipv4_header_t );

void forge_icmp_ping( void* buf , struct sockaddr* dest_addr );

void ping_loop(struct sockaddr* dest_addr );

#endif
