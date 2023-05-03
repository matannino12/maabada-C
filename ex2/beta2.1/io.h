#ifndef IO_H
#define IO_H

typedef struct {
    int flags[8];
    char *expression;
    char *filename;
}Input;

void flags_print(int flags[]);
void input_print(Input input1);
int arg_checker(char *argv[], int i);
Input Cmd_parser(int argc, char *argv[]);

#endif