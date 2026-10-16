CC = cc
CFLAGS = -std=c90 -Wall -Wextra -pedantic-errors -g

.PHONY: all clean check
all: app

app: main.c
	$(CC) $(CFLAGS) -o $@ main.c

check: app
	./app

clean:
	rm -f app tests *.o

metrics:
	python3 ../../analyze.py --block 06 --output resources/quality-report-block06.md

# Einheitlicher Test-Einstieg fuer VS Code und die Projektwurzel.
.PHONY: test
test: check
