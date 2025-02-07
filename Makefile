CC = gcc
CFLAGS = -Wall -Wextra -g

strace: strace.c
	$(CC) $(CFLAGS) -o strace strace.c

clean:
	rm -f strace
