#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "io.h"
#include "our_grep.h"

FILE *file_opener(input input1){
    FILE *fp = fopen(input1.filename, "r");
    if (fp == NULL){
        printf("Error opening file %s\n", input1.filename);
    }
    return fp;
}

Node *new_node(int data){
    Node *new_node = (Node*) malloc (sizeof(Node));
    assert(new_node);
    new_node->num = data;
    new_node->next = NULL;
    return new_node;
}

Node *append_node(Node *head_node, Node *tail_node, Node *new_node) {
    if(head_node == NULL){
        return new_node;        
    }
    tail_node->next = (Node*) malloc (sizeof(Node));
    assert(tail_node->next);
    tail_node->next = new_node;
    return head_node;
}

bool grep_searcher(char *line, input input1){
    char *expression = input1.expression;
    if(input1.flags[3] == 1){
        line = lower(line);
    }
    return (strstr(line, expression) != NULL);
}

void free_list(Node* head){
    if(head != NULL){
        free_list(head->next);
        free(head);
        head = NULL;
    }
}

void master_grep(input input1){
    FILE *fp = file_opener(input1);
    if(fp == NULL){
        return;
    }
    char *line = NULL;
    size_t line_len = 0;
    int i = 1;
    Node *tail, *head = NULL;
    while(getline(&line, &line_len, fp) != -1){    
        if(grep_searcher(line, input1)){
            Node *temp = new_node(i);
            head = append_node(head, tail, temp);
            tail = temp;
        }   
        i++;
    }
    if(head == NULL){
        return;
    }
    int file_len = i;
    rewind(fp);
    Node *print_head = head;
    for(i = 1; i<=file_len; i++){
        getline(&line, &line_len, fp);
        if(head->num == i){
            printf("%s", line);
            head = head->next;
        } 
    }
    fclose(fp);
    free(line);
    free_list(print_head);
    return;
}