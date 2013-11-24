#ifndef SET_SOCK__H_
#define SET_SOCK__H_

#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>

void connect_socket_to_host( int sockfd , int prot , char* hostname );


#endif
