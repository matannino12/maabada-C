#ifndef INPUT_GREP_H
#define INPUT_GREP_H

#include <stdbool.h>

#define A 0
#define b 1
#define c 2
#define i 3
#define n 4
#define v 5
#define x 6
#define E 7
#define All 8

typedef struct input_args {
  int flag_A;
  bool flag[All];
  char* expression;
  char* filename;
} input;

input* get_input(int argc, char* argv[]);

#endif