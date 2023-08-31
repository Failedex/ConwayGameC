
IDIR=/usr/local/include
LDIR=/usr/local/lib
CC=gcc
# OBJ= somestuff.o other.o

CFLAGS=-L$(LDIR) -I$(IDIR) -lraylib -lm

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

main: clean
	$(CC) -o $@ main.c $(CFLAGS) 

clean: 
	rm -f main
