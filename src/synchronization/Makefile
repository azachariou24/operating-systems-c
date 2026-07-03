CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

TARGET = restaurant_sync

SRC = restaurant_sync.c


all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean