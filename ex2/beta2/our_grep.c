#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "io.h"
#include "our_grep.h"

FILE *file_opener(Input input1){
    char *filename = input1.filename;
    FILE *fp = fopen(*filename, "r");
    if (fp == NULL){
        printf("Error opening file %s\n", filename);
        return NULL;
    }
    return fp;
}

void master_grep(Input input1){
    if(file_opener(input1) == NULL){
        return;
    }
    // להמשיך עם בטא 1

}