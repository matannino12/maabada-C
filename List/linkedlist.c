#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"


Node* create_node(int data) {
    Node* new_node = (Node*) malloc (sizeof(Node));
    new_node->data = data;
    assert(new_node);
    new_node->next = NULL;
    return new_node;
}


int list_len(Node* head) {
    Node* cur = head;
    int len = 0;
    while (cur != NULL){
        cur = cur->next;
        len++;
    }
    return len;
}


Node* get_ith_node(Node* head, int i) {
    int len = list_len(head), j;
    if (i >= len){
        return NULL;
    }
    Node* cur = head;
    for (j=0; j<i; j++) {
        cur = cur->next;
    }
    return cur;
}


Node** get_end_ptr(Node* head) {
    assert(head);
    Node* cur = head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    Node** cur_end_ptr = &cur;
    return cur_end_ptr;
}


void push_after(Node* node, Node* new_node) {
    new_node->next = (Node*) malloc (sizeof(Node));
    assert(new_node->next);
    new_node->next = node->next;
    if (node->next == NULL){
        node->next = (Node*) malloc (sizeof(Node));
        assert(node->next);
    }
    node->next = new_node;
}


void delete_head(Node** head_ptr) {
    Node* cur_head = *head_ptr;
    *head_ptr = cur_head->next;
    free(cur_head);
    cur_head = NULL;
}


void bypass_node(Node** head_ptr, int i) {
    Node* prev_node = get_ith_node(*head_ptr, i-1);
    Node* cur_node = prev_node->next;
    Node* next_node = cur_node->next;
    assert(prev_node && cur_node && next_node);
    prev_node->next = next_node;
    free(cur_node);
    cur_node = NULL;
}


void delete_end(Node** head_ptr) {
    int len = list_len(*head_ptr);
    Node* new_end = get_ith_node(*head_ptr, len-2);
    free(new_end->next);
    new_end->next = NULL;
}


void free_linked_list_rec(Node* head) {
    if (head != NULL) {
        free_linked_list_rec(head->next);
        free(head);
        head = NULL;
    }
}


void add_end(Node** head_ptr, int data) {
    if (*head_ptr == NULL){
        add_start(head_ptr, data);
        return;
    }
    Node* new_node = create_node(data);
    Node** cur_end_ptr = get_end_ptr(*head_ptr);
    push_after(*cur_end_ptr, new_node);
}


void add_start(Node** head_ptr, int data) {
    Node* new_node = create_node(data);
    new_node->next = (Node*) malloc (sizeof(Node));
    assert(new_node->next);
    new_node->next = *head_ptr;
    *head_ptr = new_node;
}


void add_after(Node** head_ptr, int new_data, int cur_data) {
    Node* cur = *head_ptr;
    while (cur != NULL){
        if (cur->data == cur_data){
            Node* new_node = create_node(new_data);
            push_after(cur, new_node);
            return;
        }
        cur = cur->next;
    }
    assert(cur && "index is out of range");
}


void print_index(Node** head_ptr, int data) {
    Node* cur = *head_ptr;
    int i=0;
    while (cur != NULL){
        if (cur->data == data){
            printf("%d\n", i);
            return;
        }
        i++;
        cur = cur->next;
    }
    printf("%d\n", -1);
}


void delete_index(Node** head_ptr, int i) {
    int len = list_len(*head_ptr);
    assert(i<len && "index is out of range");
    if (i == 0){
        delete_head(head_ptr);
        return;
    }
    if (i == len-1){
        delete_end(head_ptr);
        return;
    }
    bypass_node(head_ptr, i);
}


void print_list(Node** head_ptr) {
    printf("[");
    Node* cur = *head_ptr;
    while (cur != NULL){
        printf("%d", cur->data);
        if (cur->next != NULL){
            printf(", ");
        }
        cur = cur->next;
    }
    printf("]\n");
}


void free_linked_list(Node** head_ptr) {
    free_linked_list_rec(*head_ptr);
    *head_ptr = NULL;
}

