CFLAGS = -std=c99 -Wall -Wextra -pedantic
PERL = /usr/bin/env perl

all: wide bubblebabble ledanim pulse

pulse:
	@${MAKE} -C pulse

wide: wide.c
	$(CC) -o $@ $(CFLAGS) $<

bubblebabble: bubblebabble.c
	$(CC) -o $@ $(CFLAGS) $<

ledanim:
	@$(MAKE) -C ledanim

wibble: wibble.c
	$(CC) -Wall -Wextra -pedantic -lbluetooth -lcwiid -lm -o $@ $<

test:
	prove -s t/*.t

clean:
	$(RM) wide bubblebabble
	@$(MAKE) -C ledanim $@
	@${MAKE} -C pulse $@

.PHONY: test clean ledanim pulse
