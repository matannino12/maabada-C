#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "io.h"
#include "our_grep.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        // argc might be 1 if we use stdio
        return 0;
    }
    input input1 = Cmd_parser(argc, argv);
    // input_print(input1); // only for debug
    master_grep(input1);
    return 0;
}