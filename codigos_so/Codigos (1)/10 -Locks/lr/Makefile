CC = gcc
CFLAGS = -Wall -pedantic -g 
LDFLAGS = -l pthread

PROGRAMS = cond_signal cond_signal_n deadlock teste_rlock

all: $(PROGRAMS)

lr.o: lr.h lr.c
	$(CC) $(CFLAGS) -c lr.c

teste_rlock: lr.o teste_rlock.c
	$(CC) $(CFLAGS) $(LDFLAGS) lr.o teste_rlock.c -o teste_rlock

clean:
	rm -f *.o *~ $(PROGRAMS)
