#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "io.h"
#include "our_grep.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        return 0;
    }
    Input input1 = Cmd_parser(argc, argv);
    input_print(input1); // לדיבאג בלבד
    master_grep(input1);
    return 0;
}