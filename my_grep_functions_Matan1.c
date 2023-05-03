#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "io.h"

void to_lower_case(char* str);
void get_next_num_lines(FILE* fp,char* word, int num);
int get_line_length(char* line);//צריך עוד לכתוב
print_format(char* line, char* expression);//צריך עוד לכתוב 
bool is_equal(char* line, char* str);

//------------------------------------------------------------

print_format(char* line, char* expression)
{

}

bool is_equal(char* line, char* str) {
    // return True iff line is equal to str!
    return strcmp(line, str);
}

void to_lower_case(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if ('A' <= str[i] && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }
        i++;
    }
}

void get_next_num_lines(FILE* fp,char* expression, int num)
{
    // Will return the next num lines
    FILE *newfile =fp;
    char* line = NULL;
    size_t len = 0;
    int Len_line=0,Num_bits=0;
    while (getline(&line, &len,newfile) != -1)
    {
        Len_line = strlen(line);
        Num_bits += Len_line;
        if (is_equal(line, expression))
        {
            print_format(line, expression);
            for (int i = 0; i < num; i++) 
            {
                if (-1 == getline(&line, &len, newfile) != -1)
                {
                    break;
                }
                else
                {
                    getline(&line, &len, fp);
                    print_format(line, expression);
                }
            }
            printf("--\n");
            rewind(newfile);
            fseek(newfile,Num_bits,0);
        }
    }  
}

int main()
{
    FILE *fp = fopen("some_file", "r");
    if (fp == NULL){
        printf("Error opening file %s\n", "some_file");
        return ;
    }
    get_next_n_lines(fp,"arr",3);
    return 0;
}