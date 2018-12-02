CC = gcc
CFLAGS = -Wall -I./include -g
target = test

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
	 
$(target): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<  -o $@

.PHONY: clean
clean:
	rm -f $(target) $(OBJ)
