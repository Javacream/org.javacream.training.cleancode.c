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
	rm -f $(OBJECTS) $(TARGET) test_runner additional_tests_runner test-output.txt

# Der gemeinsame Test liegt im uebergeordneten Refactoring-Verzeichnis.
# main.c wird ueber test_adapter.h eingebunden; weitere Moduldateien werden gelinkt.
TEST_MODULES := $(filter-out main.c,$(wildcard *.c))
.PHONY: test
test:
	$(CC) $(CFLAGS) -I. ../test.c $(TEST_MODULES) $(LDFLAGS) -o test_runner $(LDLIBS) -lm
	./test_runner
	$(CC) $(CFLAGS) -I. additional_tests/test_subtotal.c $(TEST_MODULES) $(LDFLAGS) -o additional_tests_runner $(LDLIBS) -lm
	./additional_tests_runner
