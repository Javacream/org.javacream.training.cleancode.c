CC = cc
CFLAGS = -std=c90 -Wall -Wextra -pedantic -g

.PHONY: all clean check coverage
all: app tests

app: main.c logic.c logic.h
	$(CC) $(CFLAGS) -o $@ main.c logic.c

tests: test.c logic.c logic.h
	$(CC) $(CFLAGS) -o $@ test.c logic.c

check: tests
	./tests

coverage:
	$(CC) $(CFLAGS) --coverage -O0 -o tests-coverage test.c logic.c
	./tests-coverage
	gcov -b -c logic.c -o tests-coverage-logic.gcno
	@echo "Coverage-Details: logic.c.gcov (Zeilen und Zweige; keine Qualitätsnote)"

clean:
	rm -f app tests tests-coverage *.o *.gcda *.gcno *.gcov
