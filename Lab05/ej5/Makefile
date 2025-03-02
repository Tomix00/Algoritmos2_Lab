CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = 
OBJECTS = $(SOURCES:.c=.o)
TARGET = 

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)
