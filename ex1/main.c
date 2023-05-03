#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedlist.h"

#define MAX_LINE_SIZE 100


void to_lower_case(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if ('A' <= str[i] && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }
        i++;
    }
}


void parse_line(char string[], char** instruction_ptr, int* num1_ptr, int* num2_ptr) {
    char* token = strtok(string, " ");
    *instruction_ptr = token;
    to_lower_case(*instruction_ptr);
    token = strtok(NULL, " ");
    if (token != NULL) {
        *num1_ptr = atoi(token);
        token = strtok(NULL, " ");
        if (token != NULL) {
            *num2_ptr = atoi(token);
        }
    }
}


bool string_starts_with(char* string, char* prefix){
    int i=0;
    while (prefix[i] != '\0') {
        if (string[i] != prefix[i]) {
            return false;
        }
        i++;
    }
    return true;
}


bool execute_action(Node** head_ptr, char* instruction, int num1, int num2) {
    if (string_starts_with(instruction, "exit")){
        free_linked_list(head_ptr);
        return false;
    }
    if (string_starts_with(instruction, "add_end")){
        add_end(head_ptr, num1);
    }
    else if (string_starts_with(instruction, "add_start")){
        add_start(head_ptr, num1);
    }
    else if (string_starts_with(instruction, "add_after")){
        add_after(head_ptr, num1, num2);
    }
    else if (string_starts_with(instruction, "index")){
        print_index(head_ptr, num1);
    }
    else if (string_starts_with(instruction, "del")){
        delete_index(head_ptr, num1);
    }
    else if (string_starts_with(instruction, "print")){
        print_list(head_ptr);
    }
    return true;
}


int main() {
    Node* head = NULL;
    char line[MAX_LINE_SIZE];
    char* instruction;
    int num1, num2;
    bool read_line = true;
    while (read_line) {
        fgets(line, MAX_LINE_SIZE, stdin);
        parse_line(line, &instruction, &num1, &num2);
        read_line = execute_action(&head, instruction, num1, num2);
    }
    exit(0);
    return 0;
}

