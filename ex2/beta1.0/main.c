#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void my_grep(char* filename[], char* expression[]){
    // open the file and try reading it. if file does not open print out an error
    FILE *fp = fopen(*filename, "r");
    if (fp == NULL){
        printf("Error opening file %s\n", filename);
        return ;
    }
    // allocate memory for reading a line
    char chunk[128];
    size_t len = sizeof(chunk);
    char *line = malloc(len);
    if(line == NULL){
        printf("unable to allocate memory for the line buffer\n");
        return ;
    }
    line[0] = '\0';
    // go through the whole file
    while (fgets(chunk, sizeof(chunk), fp) != NULL){
        // if chunk is too small, reallocate memory
        while(len - strlen(line) < sizeof(chunk)){
            len *= 2;
            if((line = realloc(line, len)) == NULL){
                printf("Unable to reallocate memory for the line buffer.");
                free(line);
                return ;
            }
        }
        strcat(line, chunk);
        // if we reach the end of the line, check for expression and print if needed
        if(line[strlen(line)-1] == '\0'){
            if (strstr(line, *expression)){
                printf("%s", line);
        }
        line[0] = '\0';
    }
    // close and return
    fclose(fp);
    free(line);
    return ;
    }
}

int main(int argc, char *argv[]){
    // find expression in argv
    int expression_i;
    for(int i=0; i<argc; i++){
        if(strcmp(argv[i],"-E")==0){
            expression_i = i+1;
            break;
        }
    }

    // call my_grep
    my_grep(&argv[argc-1], &argv[expression_i]);
    return 0;
}