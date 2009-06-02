CFLAGS = -Wall -Wextra -pedantic
PERL = /usr/bin/env perl

all: wide bubblebabble hm ledanim

wide: wide.c
	$(CC) -o $@ -std=c99 $(CFLAGS) $<

bubblebabble: bubblebabble.c
	$(CC) -o $@ -std=c99 $(CFLAGS) $<

hm: hm.c
	$(CC) -o $@ -lrt $(CFLAGS) $<

ledanim:
	@$(MAKE) -C ledanim

test:
	prove -s t/*.t

clean:
	$(RM) wide bubblebabble hm
	@$(MAKE) -C ledanim $@

.PHONY: test clean ledanim
