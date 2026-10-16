CC = cc
CFLAGS = -std=c90 -Wall -Wextra -pedantic-errors -g

.PHONY: all clean check
all: app

app: main.c
	$(CC) $(CFLAGS) -o $@ main.c

check: app
	./app 2 1 0 3

clean:
	rm -f app tests *.o

# Einheitlicher Test-Einstieg fuer VS Code und die Projektwurzel.
.PHONY: test
test: check
