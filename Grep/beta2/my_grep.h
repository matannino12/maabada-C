#ifndef MY_GREP_H
#define MY_GREP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "reader1.h"
#include "input_grep.h"

char to_lower_case(char c);
bool handle_E_flags(char line_char,char expression_char,char* line,
char* expression,bool flag[]);
bool check_match_char(char line_char,char expression_char
,char* line,char* expression,bool flag[]);
bool is_match_in_line(char* line,char* expression,bool flag[]);
bool is_match(input* input1,char* line,int* match_count);
void print_pormat(input* input1,Reader* reader,char* line,bool should_be,
bool* makaf);
bool switch_match(bool is_match);
void print_Anum(input* input1,Reader* reader,char* line,int* match_count,
bool* should_be,bool* makaf);
void my_grep(input* input1,Reader* reader);



#endif
