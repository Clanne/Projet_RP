#ifndef SET_SOCK__H_
#define SET_SOCK__H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>

int create_raw_socket( int addr_family , int proto );

void get_host_addr( char* hostname , struct sockaddr* dest );

#endif
