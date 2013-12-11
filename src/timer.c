#include "timer.h"

void starttimer(timer* t){
	gettimeofday( &t->debut , NULL );
}

void stoptimer(timer* t){
	gettimeofday( &t->fin , NULL );
	t->resultat = tvdiff( t->debut , t->fin );
}

int timeout( timer* t ){
	int timeout = 0;
	struct timeval currenttv , timediff;
	gettimeofday( &currenttv , NULL );
	timediff = tvdiff( t->debut , currenttv );
	if( timediff.tv_sec >= 1 ) timeout = 1;
	return timeout;
}

timer_stats* init_tstats(){
	timer_stats* ts = malloc( sizeof(timer_stats) );
	ts->max = 0.0;
	ts->min = -1.0;
	ts->value_list = NULL;
	ts->avg = 0.0 ;
	ts->dev = 0.0 ;
	ts->totaltime = 0.0;
	return ts;
}

void free_tstats( timer_stats* ts ){
	free_list( ts->value_list );
	free( ts );
}

void print_tstats( timer_stats* ts ){
	ts->avg = calc_average( ts->value_list );
	ts->dev = calc_deviation( ts->value_list , ts->avg );
	printf("total: %0.3f, max/min/avg/dev : %0.3f/%0.3f/%0.3f/%0.3f\n" , ts->totaltime ,ts->max , ts->min ,ts->avg , ts->dev);
}

void update_timer_stats(timer* t , timer_stats* stats){
	float resultat = timeval_to_float( t->resultat );
	if( resultat >  stats->max )  stats->max = resultat;
	if( resultat < stats->min  || stats->min < 0 ) stats->min = resultat;
	stats->totaltime += resultat;
	statlist_add( &stats->value_list , resultat );
}

float last_result( timer_stats* ts ){
	return ts->value_list->time  ;
}

struct timeval tvadd( struct timeval tv1 , struct timeval tv2){
	struct timeval resultat;
	resultat.tv_sec = (tv1.tv_sec + tv2.tv_sec) + (tv1.tv_usec + tv2.tv_usec)/ 1000000;
	resultat.tv_usec = (tv1.tv_usec + tv2.tv_usec) % 1000000;
	return resultat;
}

struct timeval tvdiff( struct timeval debut , struct timeval fin  ){
	struct timeval resultat;
	resultat.tv_sec = (fin.tv_sec - debut.tv_sec) + (fin.tv_usec - debut.tv_usec ) / 1000000;
	resultat.tv_usec = (fin.tv_usec - debut.tv_usec) % 1000000;
	return resultat;
}

float timeval_to_float(struct timeval tv){
	float f = ((float)tv.tv_sec)*1000.0 + ((float)tv.tv_usec)/1000.0 ;
	return f;
}

void sprint_timeval(struct timeval* tv , char* retstr ){
	sprintf( retstr , "%0.3f" , timeval_to_float(*tv) );
}

void sprint_timervalue(timer* t , char* retstr ){
	sprint_timeval( &t->resultat , retstr );
}

void statlist_add(tv_list** list , float val ){
	tv_list* maillon = malloc( sizeof( tv_list ) );
	maillon->time = val;
	maillon->next = *list;
	*list = maillon ;
}

float calc_average( tv_list* list ){
	float sum=0.0;
	int i=0;
	tv_list*p = list;
	while( p!=NULL ){
		i++;
		sum += p->time;
		p = p->next;
	}
	return sum / (float)i ;
}

float calc_deviation( tv_list* list , float avg ){
	float sum = 0.0 ;
	int i = 0;
	tv_list*p = list;
	while( p!= NULL ){
		i++;
		sum += ( p->time - avg ) * ( p->time - avg );
		p = p->next;
	}
	return sqrt( sum/(float)i );
}

void free_list( tv_list* list ){
	tv_list*p =list;
	tv_list*tmp ;
	while( p!=NULL ){
		tmp = p;
		p = p->next;
		free(tmp);
	}
}
