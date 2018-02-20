TARGET = sistema
CFLAGS = -g -Wall
LIBS = -lm
CC = gcc

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst src/%.c, bin/%.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o bin/$@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
    $(CC) $(OBJECTS) -Wall $(LIBS) -o bin/$@

clean:
    -rm -f bin/*.o
    -rm -f $(TARGET)
