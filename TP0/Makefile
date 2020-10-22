CC=gcc

binaries=args_parser.o base64.o file_reader.o file_writer.o main.o

.PHONY: all clean
all: tp0 clean

tp0: $(binaries)
	$(CC) $(binaries) -o tp0

clean:
	rm $(binaries) 