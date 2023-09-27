#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input_grep.h"

input* init_input();
int arg_checker(char* argv);
void Set_input(input* input1, int argc, char* argv[]);

input* init_input()
{
  input* input1 = (input*)malloc(1 * sizeof(input));
  input1->flag_A = 0;
  for (int count = 0; count < All; count++) {
    input1->flag[count] = false;
  }
  input1->expression = NULL;
  input1->filename = NULL;
  return input1;
}

input* get_input(int argc, char* argv[])
{
  input* input1 = init_input();
  Set_input(input1, argc, argv);
  return input1;
}

bool is_flag(char* arg);

bool is_flag(char* arg)
{
  if (arg == NULL) {
    return false;
  }
  if (strlen(arg) != 2) {
    return false;
  }
  if (arg[0] != '-') {
    return false;
  }
  return true;
}

int arg_checker(char* argv)
{
  if (strcmp(argv, "-A") == 0) {
    return A;
  } else if (strcmp(argv, "-b") == 0) {
    return b;
  } else if (strcmp(argv, "-c") == 0) {
    return c;
  } else if (strcmp(argv, "-i") == 0) {
    return i;
  } else if (strcmp(argv, "-n") == 0) {
    return n;
  } else if (strcmp(argv, "-v") == 0) {
    return v;
  } else if (strcmp(argv, "-x") == 0) {
    return x;
  } else if (strcmp(argv, "-E") == 0) {
    return E;
  }
}

void Set_input(input* input1, int argc, char* argv[])
{
  int num, counter = 1;
  bool expression = true;
  if (argc == 0 || argc == 1) {
    printf("wrong");
    exit(0);
  }
  while (counter <= argc - 1) {
    while (is_flag(argv[counter])) {
      num = arg_checker(argv[counter]);
      if (0 == num) {
        input1->flag[A] = true;
        counter = counter + 1;
        input1->flag_A = atoi(argv[counter]);
      } else if (E == num) {
        input1->flag[E] = true;
        counter = counter + 1;
        input1->expression = argv[counter];
        break;
      } else {
        input1->flag[num] = true;
      }
      counter = counter + 1;
    }
    if (expression) {
      input1->expression = argv[counter];
      expression = false;
      counter++;
    }
    if (!expression && counter == argc - 1 & argv[counter] != NULL) {
      input1->filename = argv[counter];
      break;
    }
  }
}