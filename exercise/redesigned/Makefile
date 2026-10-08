CC = gcc
CFLAGS = -std=c90 -pedantic-errors -Wall -Wextra -Werror
PG_INCLUDEDIR = $(shell pg_config --includedir 2>/dev/null)
PG_LIBDIR = $(shell pg_config --libdir 2>/dev/null)
SOURCES = src/main.c src/order.c src/postgres_store.c
all: orders
orders: $(SOURCES) src/order.h src/postgres_store.h
	$(CC) $(CFLAGS) -I$(PG_INCLUDEDIR) -L$(PG_LIBDIR) -o orders $(SOURCES) -lpq
test: orders
	./orders --self-test
integration-test: orders
	./orders --integration-test
run: orders
	./orders
clean:
	rm -f orders
.PHONY: all test integration-test run clean
