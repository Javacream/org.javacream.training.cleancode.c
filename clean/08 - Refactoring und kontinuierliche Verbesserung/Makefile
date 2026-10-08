CC = cc
CFLAGS = -std=c90 -Wall -Wextra -pedantic

all: app tests

app: main.c
	$(CC) $(CFLAGS) -o app main.c

tests: main.c test.c
	$(CC) $(CFLAGS) -Dmain=app_main -c main.c -o main_test.o
	$(CC) $(CFLAGS) -c test.c -o test.o
	$(CC) -o tests main_test.o test.o

clean:
	rm -f app tests *.o
