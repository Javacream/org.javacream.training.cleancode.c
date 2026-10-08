CC = cc
CFLAGS = -std=c90 -Wall -Wextra -pedantic
TARGET = app

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)
