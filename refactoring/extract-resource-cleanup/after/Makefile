CC ?= cc
CFLAGS ?= -std=c90 -Wall -Wextra -Wpedantic -pedantic-errors
LDFLAGS ?=
LDLIBS ?=

SOURCES := $(filter-out contract_test.c,$(wildcard *.c))
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
	rm -f $(OBJECTS) $(TARGET) test_runner contract-tests test-output.txt

# Der gemeinsame Test liegt im uebergeordneten Refactoring-Verzeichnis.
# main.c wird ueber test_adapter.h eingebunden; weitere Moduldateien werden gelinkt.
TEST_MODULES := $(filter-out main.c contract_test.c,$(wildcard *.c))
.PHONY: test
test:
	$(CC) $(CFLAGS) -I. ../test.c $(TEST_MODULES) $(LDFLAGS) -o test_runner $(LDLIBS) -lm
	./test_runner

contract-test: contract_test.c main.c
	$(CC) $(CFLAGS) -o contract-tests contract_test.c $(LDLIBS)
	./contract-tests
	rm -f contract-tests
