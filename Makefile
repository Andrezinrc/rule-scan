TARGET = scanner
CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = main.c scanner.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
