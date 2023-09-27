#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "input_grep.h"


input* init_input(){
    input* input1= (input*)malloc(1*sizeof(input));
    input1->flag_A =0;
    for(int i=0;i<8;i++){
        input1->flag[i]=false;
    } 
    input1->expression = NULL;
    input1->filename =NULL;
    return input1;
} 

input* get_input(int argc, char *argv[]){
    input* input1=init_input();
    Set_input(input1,argc,argv);
    return input1;
}

bool is_flag(char* arg){
    if (arg == NULL) {
        return false;
    }
    if (strlen(arg) != 2) {
        return false;
    }
    if (arg[0] != '-') {
        return false;
    }
    return true;
}

void flags_print(bool flags[])
{
    printf("[");
    for(int i = 0; i < 7; i++){
        printf("%d, ",flags[i]);
    }
    printf("%d]", flags[7]);
    printf("\n");
}

void input_print(input* input1){
    flags_print(input1->flag);
    printf("%s\n", input1->expression);
    printf("%s\n", input1->filename);
}

void prints_text(int argc, char *argv[])
{
   for(int i=0;i<argc-1;i++)
   {
      printf("%d-%s,",i,argv[i]);
   }
}
int arg_checker(char* argv)
{
    if (strcmp(argv, "-A") == 0) {
        return 0;
    }
    else if(strcmp(argv, "-b") == 0){
        return 1;
    }
    else if(strcmp(argv, "-c") == 0){
        return 2;
    }
    else if(strcmp(argv, "-i") == 0){
        return 3;
    }
    else if(strcmp(argv, "-n") == 0){
        return 4;
    }
    else if(strcmp(argv, "-v") == 0){
        return 5;
    }
    else if(strcmp(argv, "-x") == 0){
        return 6;
    }
    else if(strcmp(argv, "-E") == 0){
        return 7;
    }
}

void Set_input(input* input1,int argc, char *argv[])
{
    int num;
    if(argc == 2){
        input1->expression=argv[1];
    }
    else if(argc==3){
        if(strstr("E",argv[2])!=NULL){
            input1->expression=argv[2];
        }
        else{
            input1->expression=argv[1];
            input1->filename=argv[2];
        }
    }
    else{
        input1->filename = argv[argc-1];
        for (int i = 1; i < argc - 1; i++)
        {
            if(!is_flag(argv[i])){
                input1->expression=argv[i];

            }
            else{
                num=arg_checker(argv[i]);
                if(num==7){
                    if(is_flag(argv[i+1])){
                        printf("bad boy!");
                        break;
                    }
                    input1->expression = argv[i+1];
                }
                else if(num==0){
                    input1->flag_A=atoi(argv[i+1]);
                    i=i+1;
                }
                input1->flag[num]=true;
            }
        }
    }
}