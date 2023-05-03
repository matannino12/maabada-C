#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "io.h"
#include "our_grep.h"

void master_grep(input input1){
    FILE *fp = fopen(input1.filename, "r");
    if (fp == NULL){
        printf("Error opening file %s\n", input1.filename);
        return;
    }
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, fp) != -1){    
        if (strstr(line, input1.expression) != NULL){
            printf("%s", line);
        }
    }
    fclose(fp);
    free(line);
    return;
}