#ifndef INPUT_GREP_H
#define INPUT_GREP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct input_args {
    int flag_A;
    bool flag[8];
    char* expression;
    char* filename;
} input;

input* init_input();
bool is_flag(char* arg);
void flags_print(bool flags[]);
void input_print(input* input1);
void prints_text(int argc, char *argv[]);
input* get_input(int argc, char *argv[]);
int arg_checker(char* argv);
void Set_input(input* input1,int argc, char *argv[]);



בטעות שיניתי , התכוונתי לשנות את התרגיל הסופי ובטעות שיניתי פה , סליחה//
#endif