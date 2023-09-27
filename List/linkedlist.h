#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct ListNode {
    int data;
    struct ListNode* next;
} Node;


void add_end(Node** head_ptr, int data);
void add_start(Node** head_ptr, int data);
void add_after(Node** head_ptr, int new_data, int cur_data);
void print_index(Node** head_ptr, int data);
void delete_index(Node** head_ptr, int i);
void print_list(Node** head_ptr);
void free_linked_list(Node** head_ptr);

#endif