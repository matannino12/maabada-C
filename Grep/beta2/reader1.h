#ifndef READER1_H
#define READER1_H

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>


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