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
	unsigned short int *p1,*p2;
	p1 =(unsigned short int*) &sum;
	p2 =(unsigned short int*) (&sum ) + 1;
	for (i = 0; i < length; i++)
	{
		sum += *(buff+i);
		if ( sum > 0xffff)
		{
			sum = *p1 + *p2;
		}
		
	}
	return ~(*p1);	
}


//~ int main ()
//~ {
	//~ unsigned short int addr[9] = { 0x4500,0x003c, 0x1c46, 0x4000, 0x4006,0xac10, 0x0a63, 0xac10, 0x0a0c };
	//~ printf("Checksum : %hx\n",checksum(&addr,9));
//~ }

