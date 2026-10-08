CC = cc
CFLAGS = -std=c90 -Wall -Wextra -pedantic -g

.PHONY: all clean check
all: app tests

app: main.c logic.c logic.h
	$(CC) $(CFLAGS) -o $@ main.c logic.c

tests: test.c logic.c logic.h
	$(CC) $(CFLAGS) -o $@ test.c logic.c

check: tests
	./tests

clean:
	rm -f app tests *.o
