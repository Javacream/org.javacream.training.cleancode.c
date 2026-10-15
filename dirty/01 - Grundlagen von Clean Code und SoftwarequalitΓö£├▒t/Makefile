CC = cc
CFLAGS = -std=c90 -Wall -Wextra -pedantic -g

.PHONY: all clean check
all: app

app: main.c
	$(CC) $(CFLAGS) -o $@ main.c

check: app
	./app

clean:
	rm -f app tests *.o
