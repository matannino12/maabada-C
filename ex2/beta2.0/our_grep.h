#ifndef OURGREP_H
#define OURGREP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "io.h"

typedef struct line_node {  
    int num;
    struct line_node *next;
} Node;

FILE *file_opener(input input1);
Node *new_node(int data);
Node *append_node(Node *head_node, Node *tail_node, Node *new_node);
bool grep_searcher(char *line, input input1);
void master_grep(input input1);

#endif