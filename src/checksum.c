/** \file checksum.c
 * \brief fonction de checksum 
 * calcul le checksum
 */

#include "checksum.h"
unsigned short int checksum ( void* addr, int length )
{
	unsigned short int* buff = (unsigned short int*) addr;
	unsigned int sum = 0;
	int i;
	for (i = 0; i < length; i++)
	{
		sum += *(buff+i);
		sum = pars_sum(sum);	
	}
	return ~(sum);	
}

unsigned short int checksum_udp ( void* addr, int length, unsigned int source_ip, unsigned int dest_ip )
{
	unsigned short int *psource = (unsigned short int *)&source_ip;
	unsigned short int *pdest = (unsigned short int *)&dest_ip;
	unsigned int sum = 0;
    // Add the pseudo-header                                //
    sum += *(psource++);
    sum += *psource;
    sum = pars_sum(sum);
    sum += *(pdest++);
    sum = pars_sum(sum);
    sum += *pdest;
    sum = pars_sum(sum);
    sum += htons(IPPROTO_UDP);
    sum = pars_sum(sum);
    sum += htons(length/2);
	sum = pars_sum(sum);
	sum += ~checksum(addr, length);
	sum = pars_sum(sum);
	return ~(sum);	
}

unsigned int pars_sum ( unsigned int sum )
{
    unsigned int res = sum;
	if ( sum > 0xffff)
	{
		unsigned short int *p1,*p2;
		p1 =(unsigned short int*) &res;
		p2 =(unsigned short int*) (&res ) + 1;
		res = *p1 + *p2;
	}
	return res;
}

//~ int main ()
//~ {
	//~ unsigned short int addr[9] = { 0x4500,0x003c, 0x1c46, 0x4000, 0x4006,0xac10, 0x0a63, 0xac10, 0x0a0c };
	//~ printf("Checksum : %hx\n",checksum(&addr,9));
//~ }

