CC=gcc
CFLAGS=-Wall -ansi


objects:=$(wildcard bin/*.o)

bin/contactList: bin/main.o bin/functions.o ; $(CC) -o $@ $< bin/functions.o
bin/%.o: src/%.c ; $(CC) $(CFLAGS) -c -o $@ $<
clean: ; rm $(objects) bin/contactList
