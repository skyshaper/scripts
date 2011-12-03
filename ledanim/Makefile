all: out-alix out-wii

out-alix: out-alix.c
	$(CC) -o $@ $<

out-wii: out-wii.c
	$(CC) -Wall -Wextra -pedantic -lbluetooth -lcwiid -o $@ $<

clean:
	$(RM) out-alix out-wii

.PHONY: all clean
