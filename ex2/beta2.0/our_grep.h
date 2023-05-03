#ifndef OURGREP_H
#define OURGREP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "io.h"
#include "our_grep.h"

typedef struct Line_Node {
    int num;
    struct Line_Node *next;
} Line;

FILE *file_opener(Input input1);
void master_grep(Input input1);

#endif