CFLAGS = -std=c99 -Wall -Wextra -pedantic

wide: wide.c
	$(CC) -o $@ $(CFLAGS) $<

clean: 
	$(RM) wide

.PHONY: clean
