#include "ping.h"


void sighand(int signum){
	stop = 1;
}

void forge_icmp_ping( void* buf , struct sockaddr* dest_addr ){
	
	forge_ip_header( buf ,dest_addr , protonum );
	forge_icmp_header( buf + headeroffset );
	set_icmp_type( buf + headeroffset , ECHO_REQUEST );
	
}

void ping_loop(struct sockaddr* dest_addr){
	
	char str[10];
	char buf[100];
	timer t;
	int sockfd ;
	int packreceived ;
	int nbbytes ;
	fd_set sock;
	struct timeval waittime;
	
	void* pack = malloc(128);
	forge_icmp_ping( pack , dest_addr );
	
	sockfd = create_raw_socket( addr_family , protonum );
	
	struct in_addr d ;
	d.s_addr = ((ipv4_header_t*)pack)->dest_ip;
	printf( "sending to : %s \n" , inet_ntoa( d ) );
	
	timer_stats* ts = init_tstats();
	uint16_t i = 0;
	while(!stop)
	{	
		setseqnum( pack + headeroffset , i );
		//checksums
		set_checksum_icmp( pack+headeroffset );
						
		FD_ZERO( &sock );
		FD_SET(sockfd , &sock);
		waittime.tv_sec = 1;
		waittime.tv_usec = 0;
		
		nbbytes = sendto( sockfd , pack , 28 , 0 , dest_addr ,  sizeof( struct sockaddr_in ) );
		if(nbbytes == -1)
			perror("send \n" );
		
		starttimer( &t );
		while( !timeout( &t ) ){
			packreceived = select( sockfd + 1 , &sock , NULL , NULL , &waittime );
			stoptimer( &t );
			sprint_timervalue( &t , str );
			
			if( FD_ISSET( sockfd , &sock ) && packreceived > 0 ){
				
				recvfrom( sockfd , buf , 100 , 0 , dest_addr , NULL);
				icmp_header_t* rcvpack = (icmp_header_t*)( buf + headeroffset);
				if( rcvpack->type == 0 ){
					printf("package received in %s icmp_seq:%d\n",str , ntohs( rcvpack->seqnum ));
					update_timer_stats( &t , ts );		
				}
				else printf("fail \n");
			}
		}		
		i = i + 1;
	}
	print_tstats( ts );
	free_tstats( ts );
	free(pack);
	close(sockfd);
}


int main( int argc , char* argv[] ){
	
	if( getuid() != 0 ){
		printf("You need root privileges to run this program.\n");
		exit(EXIT_SUCCESS);
	}
	
	sigset_t mask;
	sigemptyset( &mask );
	sigaddset( &mask , SIGINT );
	
	struct sigaction sa;
	sa.sa_handler = &sighand;
	sa.sa_mask = mask;
	
	if(sigaction(SIGINT , &sa , NULL ) == -1 ){
		perror("sigaction\n");
		exit(EXIT_FAILURE);
	}
	
	forge_ip_header = &forge_ipv4_header;
	
	struct sockaddr* dest_addr = malloc( sizeof (struct sockaddr_in6) ) ;
	
	get_host_addr( argv[1] , dest_addr , addr_family , protonum );
	
	ping_loop( dest_addr );
	
	free( dest_addr );
	exit(0);
	
}
