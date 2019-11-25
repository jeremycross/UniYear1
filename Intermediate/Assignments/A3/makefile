CC=gcc
CFLAGS=-Wall -ansi
INCL=includes/functions.h

objects:=$(wildcard bin/*.o)

bin/contactList: bin/main.o bin/functions.o ; $(CC) -o $@ $< bin/functions.o
bin/%.o: src/%.c $(INCL) ; $(CC) $(CFLAGS) -c -o $@ $<
clean: ; rm $(objects) bin/contactList
