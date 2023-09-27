#ifndef READER_H
#define READER_H

#include <stdbool.h>
#include <stdio.h>

typedef struct LineReader {
  FILE* file_pointer;
  long bytes_counter;
  long lines_counter;
  bool is_file;
} Reader;

Reader* get_reader(char* filename);

void free_reader(Reader* reader);

int read_next_line(Reader* reader, char** line_ptr);

#endif