#ifndef SET_SOCK__H_
#define SET_SOCK__H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netdb.h>

void get_interface_ip( char* inter , struct sockaddr* res , int sockfd );

int create_raw_socket( int addr_family , int proto );

void get_host_addr( char* hostname , struct sockaddr* dest , unsigned int ip_type , unsigned int protonum );

#endif
