#include "timer.h"

void starttimer(timer* t){
	gettimeofday( &t->debut , NULL );
}

void stoptimer(timer* t){
	gettimeofday( &t->fin , NULL );
	tvdiff( t->debut , t->fin , &t->resultat );
}

int timeout( timer* t ){
	int timeout = 0;
	struct timeval currenttv , timediff;
	gettimeofday( &currenttv , NULL );
	tvdiff( t->debut , currenttv , &timediff );
	if( timediff.tv_sec >= 1 ) timeout = 1;
	return timeout;
	
}

void tvdiff( struct timeval debut , struct timeval fin , struct timeval* resultat ){
	resultat->tv_sec = (fin.tv_sec - debut.tv_sec) + (fin.tv_usec - debut.tv_usec ) / 1000000;
	resultat->tv_usec = (fin.tv_usec - debut.tv_usec) % 1000000;
}

void sprint_timervalue(timer* t , char* retstr ){
	float f = ((float)t->resultat.tv_sec)*1000.0 + ((float)t->resultat.tv_usec)/1000.0 ;
	sprintf( retstr , "%0.3f" , f );
}
