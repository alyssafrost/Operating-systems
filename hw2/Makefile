CC     = gcc
CFLAGS = -std=gnu18 -O
OBJS   = hw2.o
EXECS  = tree

all: $(EXECS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

tree: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o $(EXECS)
	
