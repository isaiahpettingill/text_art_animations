CC = zig cc
CFLAGS = -Ofast -std=c2y -Wall -march=native -mtune=native -flto

TARGET = text_art
OUT_DIR = out

all: $(TARGET)

$(TARGET): text_art.c
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -o $(OUT_DIR)/$(TARGET) text_art.c

clean:
	rm -f $(TARGET)

.PHONY: all clean
