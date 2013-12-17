#ifndef UDP_HEADER__H_
#define UDP_HEADER__H_

/** \file upd_header.h
 * \brief header UPD (header)
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "checksum.h"
#include <string.h>
#include <arpa/inet.h>


typedef struct{
	uint16_t sourcePort;
	uint16_t destinationPort;
	uint16_t length;
	uint16_t checksum;
}udp_header_t;

/** 
 * \brief crée un udp_header_t.
 * \param buff : adresse de l'entête.
 * \param port : port de destination.
 */
void forge_udp_header(void* buff, uint16_t port);

/** 
 * \brief met a jour la source.
 * \param udp_h : header UDP.
 * \param source : port source.
 */
void set_sourcePort_udp(udp_header_t *udp_h, uint16_t source);
/** 
 * \brief met a jour la destination.
 * \param udp_h : header UDP.
 * \param destination : port de destination.
 */
void set_destinationPort_udp(udp_header_t *udp_h, uint16_t destination);
/** 
 * \brief met a jour la length.
 * \param udp_h : header UDP.
 * \param l : nouvelle valeure de length.
 */
void set_length_udp(udp_header_t *udp_h, uint16_t l);
/** 
 * \brief calcul le checksum de l'entête
 * \param udp_h : header UDP.
 */
void set_checksum_udp(udp_header_t *udp_h, unsigned int source_ip, unsigned int dest_ip);
/** 
 * \brief calcul le checksum.
 * \param udp_h : header UDP.
 * \param source : port source
 */

#endif
