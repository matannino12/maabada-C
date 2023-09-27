#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "reader1.h"
#include "input_grep.h"
#include "my_grep.h"


char to_lower_case(char c) {
  if('A'<=c && c<='Z')
  {
     return c-'A'+'a';
  }
  return c;
}
bool handle_E_flags(char line_char,char expression_char,char* line,
char* expression,bool flag[])
{
    if(expression_char =='.')
    {
        line=line+1;
        expression=expression+1;
    }
    if(expression_char == 92){
        expression=expression+1;
    }
    line_char=line[0];
    expression_char=expression[0];
    if(flag[3])
    {
        line_char=to_lower_case(line_char);
        expression_char=to_lower_case(expression_char);
    }

    check_match_char(line_char,expression_char,line,expression,flag);
}
bool check_match_char(char line_char,char expression_char
,char* line,char* expression,bool flag[])
{
    if(expression_char =='\0')
    {
        return true;
    }
    if(line_char =='\n' || line_char =='\0')
    {
        return false;
    }
    if(expression_char != line_char){
        return false;
    }
    return is_match_in_line(line+1,expression+1,flag);
}
bool is_match_in_line(char* line,char* expression,bool flag[])
{
    char line_char=line[0],expression_char=expression[0];
    if(flag[3])
    {
        line_char=to_lower_case(line_char);
        expression_char=to_lower_case(expression_char);
    }
    if(flag[6])
    {
        if(line_char=='\n' && expression_char=='\0'){
            return true;
        }
        if(line_char =='\n' || expression_char =='\0'){
            return false;
        }
    }
    if(flag[7])
    {
        handle_E_flags(line_char,expression_char,line,expression,flag);
    }
    else
    {
       check_match_char(line_char,expression_char,line,expression,flag);
    }   
}

bool is_match(input* input1,char* line,int* match_count)
{
    bool is_match=false;
    if(input1->flag[6]){
        is_match=is_match_in_line(line,input1->expression,input1->flag);
    }
    else{
        while(line[0]!='\0' && !is_match)
        {
          is_match=is_match_in_line(line,input1->expression,input1->flag);
          line=line+1;
        }
    }
    if(input1->flag[5]){
        is_match=switch_match(is_match);
    }
    if(is_match){
        *match_count=*match_count+1;
    }
    return is_match;
}
bool switch_match(bool is_match_line)
{
    if(is_match_line){
        return false;
    }
    return true;
}
    

void print_pormat(input* input1,Reader* reader,char* line,bool should_be
,bool* makaf)
{    
    if(input1->flag[2]){
        return;
    }
    if(*makaf){
      printf("--\n");
      *makaf=false;
    }
    if(input1->flag[4])
    {
        if(should_be){
        printf("%ld:",reader->lines_counter);
        }
        else{
        printf("%ld-",reader->lines_counter);
        }
    }
    if(input1->flag[1])
    {
        if(should_be){
            printf("%ld:",(reader->bytes_counter-strlen(line)));
        }
        else{
        printf("%ld-",(reader->bytes_counter-strlen(line)));
        }
    }
    printf("%s",line);
}

void print_Anum(input* input1,Reader* reader,char* line,int* match_count,
bool* should_be,bool* makaf)
{
    int count_num=0;
    while(count_num<input1->flag_A)
    {
        if(read_next_line(reader, &line)==-1){
                  free(line);
                  break;
        }
        else{
            if(is_match(input1,line,match_count)){
                *should_be=true;
                count_num=0;
            }
            else{
                count_num=count_num+1;
                *should_be=false;
            }
            print_pormat(input1,reader,line,*should_be,makaf);

        }
      free(line);
      line=NULL;
    }
    free(line);
    line=NULL;
    if(count_num==input1->flag_A){
        *makaf=true;
    }
}
void my_grep(input* input1,Reader* reader) 
{
    char* line = NULL;
    int match_count = 0;
    bool makaf=false,should_be;
    while (read_next_line(reader, &line)!=-1) {
        if (is_match(input1,line,&match_count)) {
           print_pormat(input1,reader,line,true,&makaf);
           if(input1->flag[0]){
              print_Anum(input1,reader,line,&match_count,&should_be,&makaf);
           }
        }
        free(line);
        line = NULL;
    }
    if(input1->flag[2]){
        printf("%d\n",match_count);
    }
    free(line);
    line = NULL;    
}

