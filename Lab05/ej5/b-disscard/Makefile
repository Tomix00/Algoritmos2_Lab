CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = queue_helpers.c queue.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = main

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)
