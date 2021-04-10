CC = gcc
CFLAGS = -Wall -pedantic -g -l pthread

PROGRAMS = prod-cons-basico \
prod-cons-basico-busy-wait prod-cons-basico-race        \
prod-cons-basico-atomic-inc \
prod-cons-basico-futex \
prod-cons-sem mult-prod-cons-sem \
cond_signal cond_signal_n

all: $(PROGRAMS)

clean:
	rm -f *.o *~ $(PROGRAMS)
