CFLAGS = -g -Wall -pedantic
CC = gcc

all: treex

treex: treex.o print.o
	$(CC) $(CFLAGS) $^ -o $@

%: %.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f treex
	rm -f print
	rm -f *.o