CC = cc
CFLAGS = -std=c90 -Wall -Wextra -pedantic-errors -g

.PHONY: all run test check clean
all: app tests

app: main.c rectangle.c rectangle.h
	$(CC) $(CFLAGS) -o $@ main.c rectangle.c

tests: test.c rectangle.c rectangle.h
	$(CC) $(CFLAGS) -o $@ test.c rectangle.c

run: app
	./app

test: tests
	./tests

check: test

clean:
	rm -f app tests *.o
