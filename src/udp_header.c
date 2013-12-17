#include "udp_header.h"
/** \file udp_header.c
 * \brief header UPD (header)
 */


void forge_udp_header(void* buff, uint16_t port)
{
	udp_header_t* udp_h = (udp_header_t*) buff;
	memset( udp_h, 0, sizeof(udp_header_t) );
	set_sourcePort_udp(udp_h,1025);
	set_destinationPort_udp(udp_h,port);
	set_length_udp(udp_h,8);
}

void set_sourcePort_udp(udp_header_t *udp_h, uint16_t source)
{
	udp_h->sourcePort = htons(source);
}
void set_destinationPort_udp(udp_header_t *udp_h, uint16_t destination)
{
	udp_h->destinationPort = htons(destination);
}
void set_length_udp(udp_header_t *udp_h, uint16_t l)
{
	udp_h->length = htons(l);
}
void set_checksum_udp(udp_header_t *udp_h, unsigned int source_ip, unsigned int dest_ip)
{
	udp_h->checksum = 0;
	udp_h->checksum = checksum_udp(udp_h,udp_h -> length, source_ip, dest_ip);
}
