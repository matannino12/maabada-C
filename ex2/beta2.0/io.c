#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "io.h"

void flags_print(int flags[]){
    printf("[");
    for(int i = 0; i < 7; i++){
        printf("%d, ",flags[i]);
    }
    printf("%d]", flags[7]);
    printf("\n");
}

void input_print(input input1){
    flags_print(input1.flags);
    printf("%s\n", input1.expression);
    printf("%s\n", input1.filename);
}

int arg_checker(char *argv[], int i){
    if(strcmp(argv[i], "-b") == 0){
        return 1;
    }
    else if(strcmp(argv[i], "-c") == 0){
        return 2;
    }
    else if(strcmp(argv[i], "-i") == 0){
        return 3;
    }
    else if(strcmp(argv[i], "-n") == 0){
        return 4;
    }
    else if(strcmp(argv[i], "-v") == 0){
        return 5;
    }
    else if(strcmp(argv[i], "-x") == 0){
        return 6;
    }
    return -1;
}

char *lower(char *str1){
    int str_len = strlen(str1);
    for(int i = 0; i<str_len; i++){
        if((str1[i] >= 'A')&&(str1[i] <= 'Z')){
            str1[i]+= 'a'-'A';
        }
    }
    return str1;
}

input Cmd_parser(int argc, char *argv[]){
    input input1;
    char *expression = NULL;
    int j;
    for(int i = 0; i < 8; i++){
        input1.flags[i] = 0;
    }
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-A") == 0){
            int a_num = atoi(argv[i+1]);
            input1.flags[0]= a_num;
            i++;
        }
        else if (strcmp(argv[i], "-E")==0){
            input1.flags[7] = 1;
            expression = argv[i+1];
        }
        else if(arg_checker(argv, i) != -1){
            j = arg_checker(argv, i);
            input1.flags[j] = 1;
        }
    }
    if(expression == NULL){
        expression = argv[1];
    }
    if(input1.flags[3] == 1){
        expression = lower(expression);
    }
    input1.expression = expression;
    // How do we handle filename not in argv?
    char *filename = argv[argc-1];
    input1.filename = filename;
    return input1;
}