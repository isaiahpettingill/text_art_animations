CC = zig cc
CFLAGS = -Ofast -Wall -march=native -mtune=native -flto

TARGET = text_art

all: $(TARGET)

$(TARGET): text_art.c
	$(CC) $(CFLAGS) -o $(TARGET) text_art.c

clean:
	rm -f $(TARGET)

.PHONY: all clean
