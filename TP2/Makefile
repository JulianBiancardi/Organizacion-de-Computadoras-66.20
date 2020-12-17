MAIN_SOURCES = $(wildcard src/main/*.c)

SOURCES = $(MAIN_SOURCES)

TESTS_SOURCES = $(wildcard src/tests/*.c) $(filter-out src/main/main.c, $(wildcard src/main/*.c))


## COMPILER FLAGS ##
CC = gcc
std = c99
all_errors = yes
optimize = yes
debug = yes

CFLAGS = -std=$(std)

ifdef all_errors
CFLAGS += -Wall -Werror -pedantic -pedantic-errors
endif

ifdef optimize
CFLAGS += -O3
endif

ifdef debug
CFLAGS += -ggdb -DDEBUG -fno-inline
endif

## END OF COMPILER ##

## LINKER FLAGS ##
#threads = yes
#threadsan = yes
math = yes

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

.PHONY: all tests
all: tp0

tp0: $(SOURCES)
	$(CC) $(CFLAGS)  $(SOURCES) -o tp2 $(LDFLAGS)

tests: $(TESTS_SOURCES)
	$(CC) $(CFLAGS)  $(TESTS_SOURCES) -o tests.exe $(LDFLAGS)
 
clean: 
	rm tests.exe tp2
