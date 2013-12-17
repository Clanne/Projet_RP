#ifndef CHECKSUM__H_
#define CHECKSUM__H_

/** \file checksum.h
 * \brief fonction de checksum  (header)
 * calcul le checksum
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

/** 
 * \brief calcul le checksum.
 * \param adresse de l'entête.
 * \param taille de l'entête a lire en nombre de demi-mots(2octets).
 */
unsigned short int checksum ( void* addr, int length );

unsigned short int checksum_udp ( void* addr, int length, unsigned int source_ip, unsigned int dest_ip );

unsigned int pars_sum ( unsigned int sum );

#endif
