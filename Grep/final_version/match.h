#ifndef MATCH_H
#define MATCH_H

#include <assert.h>
#include <stdbool.h>

typedef struct Match_check {
  long counter_right;
  bool Match_check;
  bool should_print_makaf;
} Match;

Match* init_match();
void set_match(Match* match1, bool flag[], char* line, char* expression);

#endif