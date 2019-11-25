CC=gcc
CFLAGG=-Wall -ansi
poetry: poetry.o ; $(CC) -o poetry poetry.o
poetry.o: poetry.c ; $(CC) $(CFLAGS) -c poetry.c
clean: ; rm poetry poetry.o

