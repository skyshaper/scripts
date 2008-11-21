CFLAGS = -std=c99 -Wall -Wextra -pedantic
PERL = /usr/bin/env perl

all: wide bubblebabble ledanim

wide: wide.c
	$(CC) -o $@ $(CFLAGS) $<

bubblebabble: bubblebabble.c
	$(CC) -o $@ $(CFLAGS) $<

ledanim:
	@$(MAKE) -C ledanim

test:
	$(PERL) -MTest::Harness -e 'runtests @ARGV' t/*.t

clean:
	$(RM) wide bubblebabble
	@$(MAKE) -C ledanim $@

.PHONY: test clean ledanim
