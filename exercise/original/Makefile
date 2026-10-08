CC = gcc
CFLAGS = -std=c90 -pedantic-errors -Wall -Wextra -Werror
all: orders
orders: src/main.c
	$(CC) $(CFLAGS) -o orders src/main.c
test: orders
	./orders --self-test
run: orders
	./orders
clean:
	rm -f orders orders.txt
.PHONY: all test run clean
