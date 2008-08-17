CFLAGS = -std=c99 -Wall -Wextra -pedantic

all: wide bubblebabble

wide: wide.c
	$(CC) -o $@ $(CFLAGS) $<

bubblebabble: bubblebabble.c
	$(CC) -o $@ $(CFLAGS) $<

clean: 
	$(RM) wide bubblebabble

.PHONY: clean
