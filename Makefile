CC = gcc

CCFLAGS  = -I inc -Wall -Wextra -Os -s
DBGFLAGS = -fsanitize=address -O0

SRCS = main.c src/*.c
OBJS = $(SRCS:.c=.o)
HDRS = inc/*.h

.PHONY: all clean z80.elf

all: z80.elf

z80.elf: $(SRCS) $(HDRS)
		 ./jsonToC.py > inc/opcodes.h
	     $(CC) $(SRCS) $(CCFLAGS) -o z80.elf
	     size z80.elf -Gd

dbg: $(SRCS) $(HDRS)
	$(CC) $(SRCS) $(DBGFLAGS) $(CCFLAGS) -o main.elf	

test: z80.elf
	valgrind -s ./z80.elf rom.gb

%.o: %.c
	$(CC) $< $(CCFLAGS) -o $@ -c

clean:
	- rm -rf ./*.o
	- rm -rf ./*.elf
