#include "reader.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

Reader* init_reader()
{
  Reader* reader = (Reader*)malloc(sizeof(Reader));
  assert(reader);
  reader->file_pointer = NULL;
  reader->bytes_counter = 0;
  reader->lines_counter = 0;
  reader->is_file = false;
  return reader;
}

Reader* get_reader(char* filename)
{
  Reader* reader = init_reader();
  if (filename != NULL) {
    reader->file_pointer = fopen(filename, "r");
    assert(reader->file_pointer);
    reader->is_file = true;
  }
  return reader;
}

void free_reader(Reader* reader)
{
  if (reader->is_file) {
    fclose(reader->file_pointer);
  }
  free(reader);
  reader = NULL;
}

int read_next_line(Reader* fr, char** line_ptr)
{
  size_t len = 0;
  if (fr->is_file) {
    if (getline(line_ptr, &len, fr->file_pointer) == -1) {
      return -1;
    }
  } else {
    if (getline(line_ptr, &len, stdin) == -1) {
      return -1;
    }
  }
  fr->bytes_counter = fr->bytes_counter + strlen(*line_ptr);
  fr->lines_counter = fr->lines_counter + 1;
  return 0;
}