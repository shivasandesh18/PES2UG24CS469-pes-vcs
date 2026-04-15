CC = gcc
CFLAGS = -Wall -Wextra -O2

OBJS = pes.o commit.o index.o object.o tree.o

pes: $(OBJS)
	$(CC) $(OBJS) -o pes -lcrypto

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o pes
