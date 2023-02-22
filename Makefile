CC = gcc

CCFLAGS  = -I inc -Wall -Wextra
DBGFLAGS = -fsanitize=address -ggdb3 -O0

SRCS = main.c src/*.c
OBJS = $(SRCS:.c=.o)
HDRS = inc/*.h

.PHONY: all clean

all: z80.elf

z80.elf: $(SRCS) $(HDRS)
	     $(CC) $(SRCS) $(CCFLAGS) -o z80.elf

dbg: $(SRCS) $(HDRS)
	$(CC) $(SRCS) $(DBGFLAGS) $(CCFLAGS) -o main.elf	

test: z80.elf
	valgrind -s ./z80.elf rom.gb

%.o: %.c
	$(CC) $< $(CCFLAGS) -o $@

clean:
	- rm -rf ./*.o
	- rm -rf ./*.elf
