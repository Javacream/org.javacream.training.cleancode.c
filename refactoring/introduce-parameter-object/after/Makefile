CC ?= cc
CFLAGS ?= -std=c90 -Wall -Wextra -Wpedantic -pedantic-errors
LDFLAGS ?=
LDLIBS ?=

SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)
TARGET := example

.PHONY: all run clean
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)
