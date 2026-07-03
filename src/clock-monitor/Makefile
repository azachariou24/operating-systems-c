CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c11 -pthread

TARGET = clock-monitor

SRC = src/main.c \
      src/clock_monitor.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all run clean