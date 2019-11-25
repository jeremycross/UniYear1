CC=gcc
CFLAGS=-Wall -ansi
INCL=compareElements.h


sortMe: sortMe.o compare_id_asc.o compare_id_desc.o compare_name_asc.o compare_name_desc.o compare_money_asc.o compare_money_desc.o
	$(CC) -o $@ sortMe.o compare_id_asc.o compare_id_desc.o compare_name_asc.o compare_name_desc.o compare_money_asc.o compare_money_desc.o

%.o: %.c $(INCL) ; $(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o sortMe
