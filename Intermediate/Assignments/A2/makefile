CC=gcc
CFLAGS=-Wall -std=c99
LIBS=-lm
fleschIndex: fleschIndex.o ; $(CC) -o fleschIndex fleschIndex.o $(LIBS)
fleschIndex.o: fleschIndex.c ; $(CC) $(CFLAGS) -c fleschIndex.c $(LIBS)
clean: ; rm fleschIndex fleschIndex.o

