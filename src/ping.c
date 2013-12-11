#include "ping.h"


void forge_icmp_ping( void* buf , struct sockaddr* dest_addr ){
	
	forge_ip_header( buf ,dest_addr , protonum );
	forge_icmp_header( buf + headeroffset );
	set_icmp_type( buf + headeroffset , ECHO_REQUEST );
	
}

int icmp_ping( void* pack  , struct sockaddr* dest_addr , int sockfd , timer_stats* ts){
	fd_set sock;
	timer t;
	struct timeval waittime;
	int success = 0 , seqnum = ((icmp_header_t*)(pack+headeroffset))->seqnum ;
	char buf[100];
	
	waittime.tv_sec = 1;
	waittime.tv_usec = 0;
		
	if( sendto( sockfd , pack , 28 , 0 , dest_addr ,  sizeof( struct sockaddr_in) ) < 0 )
		perror("send \n" );
	
	starttimer( &t );
	while( !timeout( &t ) ){
		
		FD_ZERO( &sock );
		FD_SET(sockfd , &sock);
		select( sockfd + 1 , &sock , NULL , NULL , &waittime );	
		if( FD_ISSET( sockfd , &sock ) ){
			
			recvfrom( sockfd , buf , 100 , 0 , dest_addr , NULL );
			stoptimer( &t );
			if( read_package( buf ) == seqnum ){
				if( ts != NULL ) update_timer_stats( &t , ts );
				success = 1;
			}
			else waittime = t.resultat ;
		}
	}
	return success ;
}

int read_package( void* rcvpack ){//renvoie le numéro de séquence du paquet s'il s'agit d'un ECHO REQUEST, -1 si ce n'est pas un paquet attendu
	ipv4_header_t* iph = (ipv4_header_t*)rcvpack;
	icmp_header_t* icmph = rcvpack + 4*iph->IHL;
	int seqnum = -1;
	if(icmph->type == ECHO_REPLY)
		seqnum = icmph->seqnum ;
	
	return seqnum;
}

void ping_loop(struct sockaddr* dest_addr){
	
	int sockfd , stop = 0;
	sigset_t mask;
	void* pack = malloc(128);
	
	sigemptyset( &mask );
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
		set_checksum_icmp( pack+headeroffset );
		if ( icmp_ping( pack ,  dest_addr , sockfd , ts ) == 1 ) 
			printf( "paquet recu en %0.3fms seq_num: %u\n" , last_result( ts ) , i );
		sigpending( &mask ) ;
		if( sigismember( &mask , SIGINT ) ) stop = 1 ;
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
	
	sigprocmask( SIG_SETMASK , &mask , NULL );
	
	forge_ip_header = &forge_ipv4_header;
	
	struct sockaddr* dest_addr = malloc( sizeof (struct sockaddr_in6) ) ;
	
	get_host_addr( argv[1] , dest_addr , addr_family , protonum );
	
	ping_loop( dest_addr );
	
	free( dest_addr );
	exit(0);
	
}
