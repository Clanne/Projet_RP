CFLAGS = -Wall -g
IFLAGS = -Iinclude

OPATH = obj/

vpath %.c src/
vpath %.h include/
vpath %.o obj/
vpath main bin/
vpath %.a lib/

main : ping.o ip_header.o timer.o icmp_header.o| bin
	gcc $(CFLAGS) -o main $(OPATH)ping.o  $(OPATH)timer.o $(OPATH)ip_header.o $(OPATH)icmp_header.o
	mv $@ bin/

ping.o : ping.c ping.h icmp_header.h
icmp_header.o : icmp_header.c icmp_header.h ip_header.h
ip_header.o : ip_header.c ip_header.h
timer.o : timer.c timer.h
timer_test.o : timer_test.c

%.o : | obj
	gcc $(CFLAGS) -c $< $(IFLAGS)
	mv $@ $(OPATH)

obj : 
	mkdir obj

lib : 
	mkdir lib

bin : 
	mkdir bin

clean : 
	rm obj/* bin/*
	
cleanall : clean
	rm -r lib/* doc/*

archive : 
	tar -f projet_rp.tar.gz -cvz src/*.c include/*.h makefile
