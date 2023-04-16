CC = gcc

# One cycle time scale
TOKI_WO_TOMORE = 250000

# Wait for ENTER between cycles
SINGLE_STEP = 0

# Do not check N logo and region
NO_CHECK = 0

# Strip and optimize size
S = 0

# Proxy Serial port I/O writes for console output
PROXYIO = 0

CFLAGS = -I inc -DCPU_FREQ=4194304 -DTIME_SCALE=$(TOKI_WO_TOMORE)

ifeq ($(S), 1)
	CFLAGS += -s -Os
else
	CFLAGS += -g -O0 -DDBG
endif

ifeq ($(SINGLE_STEP), 1)
	CFLAGS += -DSINGLE_STEP
endif

ifneq ($(NO_CHECK), 1)
	CFLAGS += -DCHECK_HEADER
endif

ifeq ($(PROXYIO), 1)
	CFLAGS += -DPROXYIO
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
