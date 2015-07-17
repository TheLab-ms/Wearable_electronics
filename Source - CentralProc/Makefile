CC=msp430-gcc
CFLAGS=-Os -Wall -g -mmcu=msp430g2553
CFLAGS=-Os -Wall -g -mmcu=msp430f5419a

OBJS=main.o

all: $(OBJS)
	$(CC) $(CFLAGS) -o main.elf $(OBJS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -fr main.elf $(OBJS)
