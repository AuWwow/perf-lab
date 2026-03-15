/*
 * @author  AuWwow
 * @github  https://github.com/AuWwow
 * @mail    vladdlav324@gmail.com
 * @file    linked_list.c
 * @date    2026-03-14
 */
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
typedef struct Node {
        int value;
        struct Node* next;
} Node;

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
void FillingLinkedList(Node** head);
void RecursiveFree(Node* current);
void RecursivePrint(Node* current);

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
int main(void) {

    Node* head = NULL;

    FillingLinkedList(&head);
    RecursivePrint(head);
    RecursiveFree(head);

    return 0;
}

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 

void FillingLinkedList(Node** head) {
    int cont = 1;
    while (cont) {
        printf("Enter a value for the node (or -1 to stop): ");
        int input;
        
        if (scanf("%d", &input) != 1) { 
            cont = 0;
            break;
        }
        
        if (input < 0) {
            cont = 0;
            break;
        }

        // Create a new node
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->value = input;
        new_node->next = NULL;

        // Add the new node to the end of the list
        if (*head == NULL) {
            *head = new_node;
        } else {
            Node* current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
    }
}

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
void RecursiveFree(Node* current) {
    if (current->next != NULL) {
        RecursiveFree(current->next);
    }
    free(current);
}


// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
void RecursivePrint(Node* current) {
    if (current->next != NULL) {
        RecursivePrint(current->next);
    }
    printf("addr %p: value %d\n", (void*)current, current->value);
}