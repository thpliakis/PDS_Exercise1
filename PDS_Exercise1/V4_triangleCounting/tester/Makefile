CC=gcc
CFLAGS = -O3

default: all

tester: tester.c
	$(CC) $(CFLAGS) -o $@ $^ mmio.c

.PHONY: clean

all: 	tester

test: tester
	@printf "\n** Testing tester\n\n"
	./tester s12.mtx
clean:
	rm -f tester
