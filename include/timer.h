#ifndef TIMER__H_
#define TIMER__H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

typedef struct vallist{ float time ; struct vallist* next ;} tv_list;
 
typedef struct{
	float totaltime ; 
	float avg;	 
	float min;
	float max;
	float dev;
	tv_list* value_list;
} timer_stats;

typedef struct{struct timeval debut ;  struct timeval fin ; struct timeval resultat ;} timer;

void starttimer( timer* t );

void stoptimer( timer* t );

int timeout( timer* t );

timer_stats* init_tstats();

void free_tstats( timer_stats* ts );

void print_tstats( timer_stats* ts );

struct timeval tvadd( struct timeval tv1 , struct timeval tv2);

struct timeval tvdiff( struct timeval debut , struct timeval fin );

void update_timer_stats(timer* t , timer_stats* stats );

float last_result( timer_stats* ts );

float timeval_to_float(struct timeval tv);

void sprint_timeval(struct timeval* tv , char* retstr );

void sprint_timervalue(timer* t , char* retstr);//renvoit chaine de caracteres representant le temps en ms

void statlist_add(tv_list** list , float val );

float calc_average( tv_list* list );

float calc_deviation( tv_list* list , float avg );

void free_list( tv_list* list );

#endif
