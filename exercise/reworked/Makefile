CC = gcc
CFLAGS = -std=c90 -pedantic-errors -Wall -Wextra -Werror
SOURCES = src/main.c src/order.c src/file_store.c
all: orders
orders: $(SOURCES) src/order.h src/file_store.h
	$(CC) $(CFLAGS) -o orders $(SOURCES)
test: orders
	./orders --self-test
run: orders
	./orders
clean:
	rm -f orders
.PHONY: all test run clean
