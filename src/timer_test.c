#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "timer.h"

int main(){
	
	int signum;
	timer t;
	sigset_t sset;
	char str[10];
	
	sigemptyset( &sset );
	sigaddset( &sset , SIGINT );
	sigprocmask( SIG_SETMASK , &sset , NULL );
	
	starttimer(&t);
	sigwait( &sset , &signum );
	stoptimer(&t);
	
	sprint_timervalue(&t , str);
	printf( "result: %s\n" , str );
	return 0;
}
