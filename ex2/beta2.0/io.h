#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct input_args {
    int flags[8];
    char *expression;
    char *filename;
} input;

void flags_print(int flags[]);
void input_print(input input1);
int arg_checker(char *argv[], int i);
char *lower(char *str1);
input Cmd_parser(int argc, char *argv[]);

#endif