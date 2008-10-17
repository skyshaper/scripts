CFLAGS = -std=c99 -Wall -Wextra -pedantic

all: wide bubblebabble ledanim

wide: wide.c
	$(CC) -o $@ $(CFLAGS) $<

bubblebabble: bubblebabble.c
	$(CC) -o $@ $(CFLAGS) $<

ledanim:
	@$(MAKE) -C ledanim

clean: 
	$(RM) wide bubblebabble
	@$(MAKE) -C ledanim $@

.PHONY: clean ledanim
