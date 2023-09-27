#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


#include "input_grep.h"
#include "reader1.h"
#include "my_grep.h"


int main(int argc, char *argv[]){
    input* input1=get_input(argc,argv);
    Reader* reader= get_reader(input1->filename);   
    my_grep(input1, reader);
    free(input1);
    free_reader(reader);
    return 0;
}
