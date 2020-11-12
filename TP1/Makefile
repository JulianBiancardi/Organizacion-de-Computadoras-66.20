MAIN_SOURCES = $(wildcard src/main/*.c)
QEMU_SOURCES = $(wildcard src/qemu/*.S)
NQEMU_SOURCES = $(wildcard src/nqemu/*.c)

SOURCES = $(MAIN_SOURCES)

#TESTS_SOURCES = $(filter-out src/main/main.cpp, $(wildcard src/*/*.cpp))

UNAME_S = $(shell uname -m)

## COMPILER FLAGS ##
CC = gcc
std = c99
all_errors = yes
# optimize = yes
# debug = yes

ifeq ($(UNAME_S),mips64)
	SOURCES += $(QEMU_SOURCES)
	CC_FLAGS += "-mips32 -mlong32"
else
	SOURCES += $(NQEMU_SOURCES)
endif

CFLAGS = -std=$(std)

ifdef all_errors
CFLAGS += -Wall -Werror -pedantic -pedantic-errors
endif

ifdef optimize
CFLAGS += -O3
endif

ifdef debug
-ggdb -DDEBUG -fno-inline
endif

## END OF COMPILER ##

## LINKER FLAGS ##
#threads = yes
#threadsan = yes
# math = yes

LDFLAGS = 

ifdef threads
LDFLAGS += -pthread
endif

ifdef threadsan
LDFLAGS += -fsanitize=thread
endif

ifdef math
LDFLAGS += -lm
endif

## END OF LINKER ## 

.PHONY: all
all: tp0

tp0: $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) -o tp

tests: $(TESTS_SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TESTS_SOURCES) -o tests.exe

clean: 
	rm tests.exe tp
