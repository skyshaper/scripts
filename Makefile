CFLAGS = -std=c99 -Wall -Wextra -pedantic

all: wide

wide: wide.c
	$(CC) -o wide wide.c

clean: 
	$(RM) wide
