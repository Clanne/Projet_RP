#ifndef TIMER__H_
#define TIMER__H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct{struct timeval debut ;  struct timeval fin ; struct timeval resultat ;} timer;

void starttimer( timer* t );

void stoptimer( timer* t );

void tvdiff( struct timeval debut , struct timeval fin , struct timeval* resultat );

void sprint_timervalue(timer* t , char* retstr);//renvoit chaine de caracteres representant le temps en ms

#endif
