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

metrics:
	python3 ../../analyze.py --block 06 --output resources/quality-report-block06.md
