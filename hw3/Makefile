CC     = gcc
CFLAGS = -std=gnu18 -O
OBJS   = hw3.o
EXECS  = tree

all: $(EXECS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

tree: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o $(EXECS)