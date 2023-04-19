#
# Awesome flags collection
# Copyright (C) 2021, 2022 ded32, the TXLib creator
#
CFLAGS += -g -static-pie -fmax-errors=100 -Wall -Wextra -Waggressive-loop-optimizations      \
          -Wcast-align -Wcast-qual -Wpedantic -Wchar-subscripts -Wconversion -Wempty-body    \
          -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 \
          -Winline -Wlarger-than=8192 -Wlogical-op -Wmissing-declarations -Wopenmp-simd      \
          -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wstack-usage=8192    \
          -Wstring-compare -Wstrict-overflow=2 -Wsign-compare -Wsuggest-attribute=noreturn   \
          -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused     \
          -Wvariadic-macros -Wrestrict -Wno-missing-field-initializers -Wno-narrowing        \
          -Wbad-function-cast -Wvla -Wzero-length-bounds -Wmissing-parameter-type            \
          -Wmissing-prototypes -Wnested-externs -Wstrict-prototypes -Wunused-value           \
          -Wpointer-sign -Wno-varargs -fcheck-new -fstack-protector                          \
          -fstrict-overflow -fno-omit-frame-pointer -fPIE -lm -pie
