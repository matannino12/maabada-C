#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wordList.h"
#include "io.h"

void to_lower_case(char* str);
void get_next_num_lines(FILE* fp,char* word, int num);
int get_line_length(char* line);
print_format(char* line, char* expression);
bool is_equal(char* line, char* str);

//------------------------------------------------------------
void printLines(Node *head) {

    char pLine[MAXLINE];
    int pLineNum = 0;
    WordNode *pWordNums;
    while(head)
    {
        head = rmFromHead(head, pLine, &pLineNum, &pWordNums);
        printf("Line %d, word(s)",pLineNum);

        while (pWordNums)
        {
            WordNode *temp = pWordNums;
            printf(" %d,", pWordNums->wordNum);
            pWordNums = pWordNums->next;
            free(temp);
        }
        printf("\b");
        printf(": %s",pLine);
    }
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
            fseek(newfile,b,0);
        }
    }  
}

int main(int argc, char*argv[])
{
    if (argc != 3)
    {
        printf("myGrep: Improper number of arguments\n"
               "Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }
    else
    {
        FILE *file = NULL;
        file = fopen(argv[2], "r");

        if (file == NULL)
        {
            printf("myGrep: Unable to open file: %s\n", argv[2]);
            return 2;
        }
        else
        {
            int lineCount,wordNum;
            char* line = NULL;  /* lines of file will be read into line; line will be searched for occurrences */
            char *delim = " .()\"\n";
            int lineNum = 0;
            Node *head = NULL;
            Node *tail = NULL;
            while (getline(&line, &len, fp) != -1)
            {
                wordNum = 0;
                lineCount = strlen(line);
                char *ptr;
                ptr = strtok(line, delim);
                while (ptr)
                {
                    if (!strcmp(ptr,argv[1]))
                    {
                        tail = addToTail(tail, line, lineNum, wordNum);
                        if (!head)  /* If the first node of the linked list has been created, it is set as the head*/
                            head = tail;
                    }
                    ptr = strtok(NULL, delim);
                    wordNum++;
                }
                lineNum++;
            }
            printLines(head);
            fclose(file);
            return 0;
        }
    }
}


