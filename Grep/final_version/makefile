CC = gcc -w


.SILENT: clang-format
.SILENT: clang-tidy

.SILENT: input_grep
.SILENT: input_grep.o
.SILENT: reader.o
.SILENT: match.o
.SILENT: main.o
.SILENT: test1
.SILENT: all
.SILENT: clean

my_grep: main.o

input_grep.o: input_grep.c input_grep.h
	$(CC) input_grep.c -c

reader.o: reader.c reader.h
	$(CC) reader.c -c

match.o: match.c match.h
	$(CC) match.c -c

main.o: main.c input_grep.o match.o reader.o
	$(CC) main.c input_grep.o match.o reader.o -o my_grep

test:
	nimrodav/grep_tests/run_all.sh

all: my_grep	

clean:
	rm -f my_grep input_grep.o match.o reader.o main.o