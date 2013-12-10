/** \file checksum.h
 * \brief fonction de checksum  (header)
 * calcul le checksum
 */

#include <stdlib.h>
#include <stdio.h>

/** 
 * \brief calcul le checksum.
 * \param adresse de l'entête.
 * \param taille de l'entête a lire en nombre de demi-mots(2octets).
 */
unsigned short int checksum ( void* addr, int length );

