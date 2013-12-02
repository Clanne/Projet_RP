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
	
	ping->ipv4h.identification = htons(321);
	
	forge_icmp_header( &ping->icmph );
	set_icmp_type( &ping->icmph , ECHO_REQUEST );
	
	return ping;
}

void ping_loop(struct sockaddr* dest_addr , package_t* pack){
	
	ipv4_header_t* iph ;
	char str[10];
	int buf[100];
	timer t;
	int sockfd ;
	int packreceived , on;
	int nbbytes ;
	
	if( ( sockfd = socket( AF_INET , SOCK_RAW , IPPROTO_ICMP ) ) == -1 ){
		perror( "socket creation failed\n" );
		exit( EXIT_FAILURE );
	}
	
	if(setsockopt( sockfd , IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
    {
        perror("setsockopt() for IP_HDRINCL error");
        exit(EXIT_FAILURE);
    }
	
	fd_set sock;
	FD_ZERO( &sock );
	FD_SET(sockfd , &sock);
	
	struct timeval timeout;
	
	struct sockaddr_in* ipv4_dest_addr = (struct sockaddr_in* ) dest_addr ;
	pack->ipv4h.dest_ip = ipv4_dest_addr->sin_addr.s_addr ;
	
	char* dest_ad;
	struct in_addr test = { pack->ipv4h.dest_ip };
	dest_ad = inet_ntoa( test );
	printf("%s\n" , dest_ad );
	
	pack->ipv4h.source_ip = inet_addr("172.17.13.115");

	//checksums
	pack->icmph.checksum = cksum((uint16_t*) &pack->icmph , sizeof(icmp_header_t) );
	pack->ipv4h.checksum = cksum((uint16_t*) &pack , sizeof(package_t) );


	int i;
	for (i = 0; i < 5 ; i++)
	{
		
		FD_ZERO( &sock );
		FD_SET(sockfd , &sock);
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		
		nbbytes = sendto( sockfd , (void*)pack , sizeof( package_t ) , 0 , dest_addr ,  sizeof( struct sockaddr_in ) );
		if(nbbytes == -1)
			perror("send \n" );
		
		starttimer( &t );
		packreceived = select( sockfd + 1 , &sock , NULL , NULL , &timeout );
		stoptimer( &t );
		sprint_timervalue( &t , str );
		
		if( FD_ISSET( sockfd , &sock ) && packreceived > 0 ){
			
			//~ socklen_t addrlen = sizeof( struct sockaddr_in );
			printf("package received in %s\n",str);
			recvfrom( sockfd , buf , 100 , 0 , dest_addr , NULL);
			iph = (ipv4_header_t* ) buf ;
			package_t* icmphdr = (package_t*) buf;
			printf("%d\n" , icmphdr->icmph.type);
			struct in_addr ia = { iph->source_ip } ;
			dest_ad = inet_ntoa( ia );
			if( icmphdr->icmph.type == 0 ) printf("We got a reply!\n");
			printf( "version:%d from:%s\n" , iph->version >> 4 ,dest_ad );
		}
		else printf("fail \n");
	}
	
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
	exit(0);
	
}
