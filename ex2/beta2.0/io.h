#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "io.h"
#include "our_grep.h"

typedef struct {
    int flags[8];
    char *expression;
    char *filename;
}Input;

void flags_print(int flags[]);
void input_print(Input input1);
int arg_checker(char *argv[], int i);
Input Cmd_parser(int argc, char *argv[]);

#endif