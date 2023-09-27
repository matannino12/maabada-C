#include "match.h"
#include "input_grep.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROUND_BRACKET 40
#define DOT 46
#define SQUARE_BRACKET 91
#define BACKSLASH 92

bool is_match_in_line(char* line, char* expression, bool flag[]);
bool check_match_char(char* line, char* expression, bool flag[]);
bool handle_E(char* line, char* expression, bool flag[]);

bool backslash(char* line, char* expression, bool flag[]);
void splitString(char* input, char** combined1, char** combined2);
bool square_bracket(char* line, char* expression, bool flag[]);
bool round_bracket(char* line, char* expression, bool flag[]);

bool switch_match(bool is_match_line);
char to_lower_case(char Tolower);

Match* init_match()
{

  Match* match1 = (Match*)malloc(sizeof(Match));
  assert(match1);
  match1->counter_right = 0;
  match1->Match_check = false;
  match1->should_print_makaf = false;
  return match1;
}

void set_match(Match* match1, bool flag[], char* line, char* expression)
{
  match1->Match_check = false;
  if (flag[x]) {
    match1->Match_check = is_match_in_line(line, expression, flag);
  } else {
    while (line[0] != '\0' && !match1->Match_check) {
      match1->Match_check = is_match_in_line(line, expression, flag);
      line = line + 1;
    }
  }
  if (flag[v]) {
    match1->Match_check = switch_match(match1->Match_check);
  }
  if (match1->Match_check) {
    match1->counter_right = match1->counter_right + 1;
  }
}

bool is_match_in_line(char* line, char* expression, bool flag[])
{
  if (flag[E]) {
    handle_E(line, expression, flag);
  } else {
    check_match_char(line, expression, flag);
  }
}

bool check_match_char(char* line, char* expression, bool flag[])
{
  char line_char = 0, expression_char = 0;
  if (line != NULL && expression != NULL) {
    line_char = line[0];
    expression_char = expression[0];
  }
  if (flag[i]) {
    line_char = to_lower_case(line_char);
    expression_char = to_lower_case(expression_char);
  }
  if (flag[x]) {
    if ((line_char == '\n' || line_char == '\0') && expression_char == '\0') {
      return true;
    } else if (line_char == '\n' || line_char == '\0' || expression_char == '\0') {
      return false;
    }
  } else {
    if (expression_char == '\0') {
      return true;
    }
    if (line_char == '\n' || line_char == '\0') {
      return false;
    }
  }
  if (expression_char != line_char) {
    return false;
  }
  return is_match_in_line(line + 1, expression + 1, flag);
}

bool handle_E(char* line, char* expression, bool flag[])
{
  if (expression[0] == ROUND_BRACKET) {
    return round_bracket(line, expression, flag);
  }
  if (expression[0] == DOT) {
    return (is_match_in_line(line + 1, expression + 1, flag));
  }
  if (expression[0] == SQUARE_BRACKET) {
    return square_bracket(line, expression, flag);
  }
  if (expression[0] == BACKSLASH) {
    return backslash(line, expression, flag);
  } else {
    check_match_char(line, expression, flag);
  }
}

bool backslash(char* line, char* expression, bool flag[])
{
  char expression_char;
  expression = expression + 1;
  expression_char = expression[0];
  if (expression_char != line[0]) {
    return false;
  }
  return is_match_in_line(line + 1, expression + 1, flag);
}

bool round_bracket(char* line, char* expression, bool flag[])
{
  char* combined1;
  char* combined2;
  splitString(expression, &combined1, &combined2);
  bool result = is_match_in_line(line, combined1, flag) || is_match_in_line(line, combined2, flag);
  free(combined1);
  free(combined2);
  return result;
}

bool square_bracket(char* line, char* expression, bool flag[])
{
  char* openingBracket = strchr(expression, '[');
  char* closeBracket = strchr(expression, ']');
  char* pipe = strchr(expression, '-');
  if (openingBracket == NULL || closeBracket == NULL || pipe == NULL) {
    exit(0);
  }
  expression = expression + (expression - openingBracket) + 1;
  char expression_first_char = expression[0];
  expression = expression + (closeBracket - pipe);
  char expression_last_char = expression[0];
  expression = expression + (closeBracket - expression) + 1;
  char line_char = line[0];
  if (flag[i]) {
    expression_first_char = to_lower_case(expression_first_char);
    expression_last_char = to_lower_case(expression_last_char);
    line_char = to_lower_case(line_char);
  }
  if (line_char < expression_first_char || line_char > expression_last_char) {
    return false;
  } else {
    return (is_match_in_line(line + 1, expression, flag));
  }
}

bool switch_match(bool is_match_line)
{
  if (is_match_line) {
    return false;
  }
  return true;
}

char to_lower_case(char Tolower)
{
  if ('A' <= Tolower && Tolower <= 'Z') {
    return Tolower - 'A' + 'a';
  }
  return Tolower;
}

void splitString(char* expression, char** combined1, char** combined2)
{
  // Find the positions of '(' and '|' characters
  char* openingBracket = strchr(expression, '(');
  char* closeBracket = strchr(expression, ')');
  char* pipe = strchr(expression, '|');
  // Calculate the lengths of the substrings
  size_t str_Len_fi = pipe - openingBracket - 1;
  size_t str_Len_se = closeBracket - pipe - 1;
  size_t str_Len_th = strlen(expression) - (closeBracket - openingBracket) - 1;
  // Allocate memory for the combined string
  *combined1 = (char*)malloc((str_Len_fi + str_Len_th + 1) * sizeof(char));
  assert(combined1);
  *combined2 = (char*)malloc((str_Len_se + str_Len_th + 1) * sizeof(char));
  assert(combined2);
  strncpy(*combined1, expression + 1, str_Len_fi);
  strncpy(*combined1 + str_Len_fi, closeBracket + 1, str_Len_th);
  (*combined1)[str_Len_fi + str_Len_th] = '\0';
  strncpy(*combined2, pipe + 1, str_Len_se);
  strncpy(*combined2 + str_Len_se, closeBracket + 1, str_Len_th);
  (*combined2)[str_Len_se + str_Len_th] = '\0';
}