#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input_grep.h"
#include "match.h"
#include "reader.h"

void my_grep(input* input1, Reader* reader, Match* match1);
void print_pormat(input* input1, Reader* reader, Match* match1, char* line);
void print_Anum(input* input1, Reader* reader, Match* match1, char* line);

int main(int argc, char* argv[])
{
  input* input1 = get_input(argc, argv);
  Reader* reader = get_reader(input1->filename);
  Match* match1 = init_match();
  my_grep(input1, reader, match1);
  free(input1);
  free_reader(reader);
  free(match1);
  return 0;
}

void my_grep(input* input1, Reader* reader, Match* match1)
{
  char* line = NULL;
  while (read_next_line(reader, &line) != -1) {
    set_match(match1, input1->flag, line, input1->expression);
    if (match1->Match_check) {
      print_pormat(input1, reader, match1, line);
      if (input1->flag[A]) {
        print_Anum(input1, reader, match1, line);
      }
    }
    free(line);
    line = NULL;
  }
  if (input1->flag[c]) {
    printf("%ld\n", match1->counter_right);
  }
  free(line);
  line = NULL;
}

void print_pormat(input* input1, Reader* reader, Match* match1, char* line)
{
  if (input1->flag[c]) {
    return;
  }
  if (match1->should_print_makaf) {
    printf("--\n");
    match1->should_print_makaf = false;
  }
  if (input1->flag[n]) {
    if (match1->Match_check) {
      printf("%ld:", reader->lines_counter);
    } else {
      printf("%ld-", reader->lines_counter);
    }
  }
  if (input1->flag[b]) {
    if (match1->Match_check) {
      printf("%ld:", (reader->bytes_counter - strlen(line)));
    } else {
      printf("%ld-", (reader->bytes_counter - strlen(line)));
    }
  }
  printf("%s", line);
}

void print_Anum(input* input1, Reader* reader, Match* match1, char* line)
{
  int count_num = 0;
  while (count_num < input1->flag_A) {
    if (read_next_line(reader, &line) == -1) {
      free(line);
      break;
    } else {
      set_match(match1, input1->flag, line, input1->expression);
      if (match1->Match_check) {
        count_num = 0;
      } else {
        count_num = count_num + 1;
      }
      print_pormat(input1, reader, match1, line);
    }
    free(line);
    line = NULL;
  }
  if (count_num == input1->flag_A) {
    match1->should_print_makaf = true;
  }
}
