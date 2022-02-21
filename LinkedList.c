//
// Created by LIM KEI YIANG on 21/2/22.
//

#include "LinkedList.h"


void insert(LinkedList *list, int value) {
    struct Node *newnode;
    newnode = (struct node *) malloc(sizeof(struct Node));

    newnode->data = value;
    newnode->next = NULL;

    if(list->head == NULL){
        // If LinkedList is empty
        list->head = newnode;

    }else{
        // If LinkedList is not empty
       list->tail->next = newnode;
    }
    list->tail = newnode;
}

void printList(struct Node *head)
{
    while (head != NULL) {
        printf("%d ", head->data);
        head= head->next;
    }
    printf("\n");
}
// pos : index of where it should be inserted
void insertAt(LinkedList *list, int pos, int value) {
    struct Node *node;
    node = (struct node *) malloc(sizeof(struct Node));
    struct Node *curr = list->head;

    node->data = value;
    node->next = NULL;
    int count = -1;
    while (curr->next != NULL){
        if (pos == 0){
            node->next = curr;
            list->head = node;
            break;
        }else{
            if(count < pos - 2 || count > pos - 2){
                curr = curr->next;
            }else{
                node->next = curr->next;
                curr->next = node;
            }
            count ++;
        }
    }

}

void delete(LinkedList *list, int pos) {
    if(list->head == NULL){
        return;
    }

    struct Node *node, *temp;

    // Store the head
    temp = list->head;
    int i;


    if(pos == 0){
        node =list->head;
        list->head = list->head->next;
        free(node);
        return;
    }

    for(i = 0; temp != NULL && i < pos - 1; i++){
        temp = temp->next;
    }

    if(temp == NULL || temp->next == NULL){
        return;
    }

    node = temp->next->next;
    free(temp->next);

    temp->next = node;

}
