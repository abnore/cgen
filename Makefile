CC = gcc
CFLAGS = -Wall -Wextra
DEBUG_FLAGS =

ifdef DEBUG
DEBUG_FLAGS = -DDEBUG
endif

all: generate

generate: generator.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o generate generator.c

clean:
	rm -f generate

