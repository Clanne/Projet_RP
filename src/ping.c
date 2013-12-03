#include "ping.h"


char* gethostip(){
    char buffer[256];
    struct hostent* h;
     
    gethostname(buffer, 256);
    h = gethostbyname(buffer);
     
    return inet_ntoa(*(struct in_addr *)h->h_addr);
     
}

package_t* forge_ping_pack(  ){
	package_t* ping = malloc( sizeof( package_t ) );
	
	forge_ipv4_header( &ping->ipv4h );
	set_TTL( &ping->ipv4h , 50 );
	set_packet_length( &ping->ipv4h , sizeof( package_t ) );
	set_protocol( &ping->ipv4h , IPPROTO_ICMP );
	
	ping->ipv4h.identification = htons(123);
	
	forge_icmp_header( &ping->icmph );
	set_icmp_type( &ping->icmph , ECHO_REQUEST );
	
	return ping;
}

void ping_loop(struct sockaddr* dest_addr , package_t* pack){
	
	char str[10];
	char* reply_addr ;
	int* buf = malloc( 128 );
	timer t;
	//~ int packreceived;
	int sockfd = create_raw_socket( AF_INET , IPPROTO_ICMP );
	
	socklen_t addr_length = sizeof( struct sockaddr_in );
	
	fd_set sock;
	FD_ZERO( &sock );
	FD_SET(sockfd , &sock);
	
	struct timeval tout;
	
	//~ ((struct sockaddr_in*)dest_addr)->sin_port =  3490 ;
	
	struct sockaddr_in* ipv4_dest_addr = (struct sockaddr_in* ) dest_addr ;
	
	printf("Sending pings to:%s\n" , inet_ntoa(ipv4_dest_addr->sin_addr));
	
	set_destination( &pack->ipv4h , ipv4_dest_addr->sin_addr.s_addr );
	
	set_source( &pack->ipv4h , inet_addr("172.17.14.10") );

	//checksums
	pack->icmph.checksum = cksum((uint16_t*) &pack->icmph , sizeof(icmp_header_t) );
	pack->ipv4h.checksum = cksum((uint16_t*) &pack , sizeof(package_t) );


	int i, nbrecv = 0;
	for (i = 0; i < 5 ; i++)
	{
		
		pack->icmph.seqnum = htons(i);
		printf("send %d\n" , ntohs( pack->icmph.seqnum ) );
		
		FD_ZERO( &sock );
		FD_SET(sockfd , &sock);
		tout.tv_sec = 1;
		tout.tv_usec = 0;
		
		if( sendto( sockfd , (void*)pack , sizeof( package_t ) , 0 , dest_addr ,  addr_length ) == -1 )
			perror("send() error \n" );
		
		starttimer( &t );
		select( sockfd + 1 , &sock , NULL , NULL , &tout );
		stoptimer( &t );
		sprint_timervalue( &t , str );
		
		if( FD_ISSET( sockfd , &sock ) ){
		
			recvfrom( sockfd , buf , 100 , 0 , dest_addr , NULL);
			
			package_t* rcvdpck = (package_t*) buf;
			printf("id: %d seq:%d\n", ntohs(rcvdpck->icmph.id), ntohs(rcvdpck->icmph.seqnum) );
			stoptimer( &t );
			sprint_timervalue( &t , str );
			printf("package received in %s\n",str);
			nbrecv ++;
			struct in_addr ia = { rcvdpck->ipv4h.source_ip } ;
			reply_addr = inet_ntoa( ia );
			if( rcvdpck->icmph.type == 0 ) printf("We got a reply!\n");
			printf( "version:%d from:%s\n" , rcvdpck->ipv4h.version >> 4 , reply_addr );
		}		
	}	
	
	printf("number of successfull pings: %d\n" , nbrecv );	
	close(sockfd);
}

uint16_t cksum(uint16_t *addr, int len)
{
    int nleft = len;
    int sum = 0;
    uint16_t *w = addr;
    uint16_t answer = 0;

    while (nleft > 1)
    {
      sum += *w++;
      nleft -= 2;
    }

    if (nleft == 1)
    {
      *(unsigned char *)(&answer) = *(unsigned char *)w;
      sum += answer;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = ~sum;

    return answer;
}

int main( int argc , char* argv[] ){
	
	if( getuid() != 0 ){
		printf("You need root privileges to run this program.\n");
		exit(EXIT_SUCCESS);	
	}
	
	package_t* pack = forge_ping_pack(  );
	
	struct sockaddr* dest_addr = malloc( sizeof (struct sockaddr_in) ) ;
	
	get_host_addr( argv[1] , dest_addr );
	
	ping_loop( dest_addr , pack );

	exit(EXIT_SUCCESS);
}
