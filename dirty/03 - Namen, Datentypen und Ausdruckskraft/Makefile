CC = cc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g

.PHONY: all clean check
all: app

app: main.c
	$(CC) $(CFLAGS) -o $@ main.c

check: app
	./app 2 1 0 3

clean:
	rm -f app tests *.o
