CC = gcc

CFLAGS  = -I inc

ifeq ($(S), 1)
	CFLAGS += -s -Os
else
	CFLAGS += -g -O0 -DDBG
endif

include txx.mk

SRCS = main.c src/*.c
OBJS = $(SRCS:.c=.o)
HDRS = inc/*.h

.PHONY: all clean z80.elf

all: z80.elf

z80.elf: $(SRCS) $(HDRS)
		 @echo CC $(SRCS)
	     $(CC) $(SRCS) $(CFLAGS) -o z80.elf
	     @ls -l z80.elf

%.lst: %.c
	$(CC) $< -I inc -Wall -Wextra -Os -o $@ -S -s

dbg: $(SRCS) $(HDRS)
	$(CC) $(SRCS) $(DBGFLAGS) $(CFLAGS) -o main.elf	

test: z80.elf
	valgrind -s ./z80.elf rom.gb

%.o: %.c
	$(CC) $< $(CFLAGS) -o $@ -c

clean:
	- rm -rf ./*.o
	- rm -rf ./*.elf
