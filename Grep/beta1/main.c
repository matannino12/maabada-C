#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void my_grep(char *filename, char *expression){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Error opening file %s\n", filename);
        return;
    }
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, fp) != -1){    
        if (strstr(line, expression) != NULL){
            printf("%s", line);
        }
    }
    fclose(fp);
    free(line);
    return;
}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Wrong number of arguments!\n");
        return 1;
    }
    char *expression = argv[1];
    char *filename = argv[2];
    my_grep(filename, expression);
    return 0;
}