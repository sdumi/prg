
# $Id: Makefile,v 1.9 2000/09/08 13:49:37 panu Exp $

CC = gcc
CFLAGS = -O3 -Wall
bfobj = bfc.o bft.o bfo.o
bfsrc = $(bfobj:.o=.c)

exec = bfi bfc

all: $(exec)

bfc: $(bfobj)

$(bfobj): bfc.h

bfc-debug: $(bfsrc)
	$(CC) $(CFLAGS) -pg -o $@ $^

clean: gc
	rm -f $(exec) bfc-debug *.o
	$(MAKE) -C src-bf clean

gc:
	rm -f *~ .#* core

