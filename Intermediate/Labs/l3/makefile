CC=gcc
CFLAGS=-Wall -ansi
enterStudents: enterStudents.o ; $(CC) -o enterStudents enterStudents.o
enterStudents.o: enterStudents.c ; $(CC) $(CFLAGS) -c enterStudents.c
clean: ; rm enterStudents enterStudents.o
