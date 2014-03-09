CC=gcc
CFLAGS=-O2

seq-sort: sequential.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f seq-sort
