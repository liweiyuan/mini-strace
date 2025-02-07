CC = gcc
CFLAGS = -Wall -Wextra -g

strace: strace.c
	$(CC) $(CFLAGS) -o mini-strace strace.c

clean:
	rm -f mini-strace
