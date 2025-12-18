CC = gcc
CFLAGS = -Wall -pthread
SRC = src/main.c src/scanner.c
OBJ = scanner

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ)

clean:
	rm -f $(OBJ)
