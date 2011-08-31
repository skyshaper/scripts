PREFIX ?= /usr/local

all: pulse

pulse: pulse.c
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $<

install: pulse
	install pulse ${PREFIX}/bin/pulse

uninstall:
	rm -f ${PREFIX}/bin/pulse

clean:
	rm -f pulse

.PHONY: all install uninstall clean
