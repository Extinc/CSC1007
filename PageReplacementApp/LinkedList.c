//
// SinglyLinkedList
//

#include "LinkedList.h"

void insert(LinkedList *list, int value) {
    struct Node *newnode;
    newnode = (struct Node *) malloc(sizeof(struct Node));

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


// pos : index of where it should be inserted
void insertAt(LinkedList *list, int pos, int value) {
    struct Node *node;
    node = (struct Node *) malloc(sizeof(struct Node));
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


int isEmpty(struct Node *head) {
    return 0;
}

void EmptyList(LinkedList *list) {


    struct Node *temp_head, *temp_tail, *node;

    // Store the head
    temp_head = list->head;
    temp_tail = list->tail;
    int i;

    if(list != NULL){
        while (list->head != NULL){
            delete(list, 0);
        }
    }

}

int search(LinkedList *list, int searchval) {
    struct Node *node;
    node = list->head;
    int count = 0;
    while (node != NULL){
        if (node->data == searchval){
            return count;
        }
        node = node->next;
        count++;
    }
    return -1;
}

int get(LinkedList *list, int pos) {
    struct Node *node;
    node = list->head;

    int count = 0;
    while (node != NULL){
        if(count == pos){
            return node->data;
        }
        node = node->next;
        count++;
    }
    return -1;
}
int getIndex(LinkedList *list, int value) {
    if(list->head == NULL){
        return -1;
    }

    struct Node *node;
    node = list->head;

    int count = 0;
    while (node != NULL){
        if(node->data == value){
            return count;
        }
        node = node->next;
        count++;
    }
    return -1;
}
int getSize(LinkedList *list) {
    struct Node *node;
    node = list->head;
    int count = 0;
    while (node != NULL){
        count++;
        node = node->next;
    }
    return count;
}
// PRINTING OF LINKEDLIST
void printList(LinkedList *list)
{
    struct Node *node = list->head;
    while (node != NULL) {
        printf("%d ", node->data);
        node= node->next;
    }
    printf("\n");
}
void printStep(LinkedList *list, int framesize) {

    struct Node *node = list->head;
    int count = 0;
    while (node != NULL) {
        printf("%d\t", node->data);
        node= node->next;
        count++;
    }

    while (count < framesize){
        printf("%d\t", -1);
        count++;
    }
    printf("\n");
}

void replace(LinkedList *list, int value, int index) {
    struct Node *node;
    node = list->head;
    int count = 0;
    while(node != NULL){
        if(count == index){
            node->data = value;
        }
        count++;
        node = node->next;
    }

}


