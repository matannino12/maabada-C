#ifndef OURGREP_H
#define OURGREP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "io.h"

typedef struct line_node {  
    int num;
    struct line_node *next;
} line;

void master_grep(input input1);

#endif