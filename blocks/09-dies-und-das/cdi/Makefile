CC ?= cc
CFLAGS ?= -std=c90 -Wall -Wextra -Werror -pedantic
BUILD = build

.PHONY: all run test clean
all: $(BUILD)/demo $(BUILD)/test_application

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/demo: src/main.c src/application.c src/application.h src/console_storage.c | $(BUILD)
	$(CC) $(CFLAGS) -Isrc src/main.c src/application.c src/console_storage.c -o $@

$(BUILD)/test_application: test/test_application.c src/application.c src/application.h | $(BUILD)
	$(CC) $(CFLAGS) -Isrc test/test_application.c src/application.c -o $@

run: $(BUILD)/demo
	./$(BUILD)/demo

test: $(BUILD)/test_application
	./$(BUILD)/test_application

clean:
	rm -rf $(BUILD)
