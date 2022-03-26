//
// SinglyLinkedList
//

#include "LinkedList.h"

//Insert Value into LinkedList at the end
void insert(LinkedList *list, int value) {
    // allocate memory to the node
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    // This will be used at step 5
    struct Node *last = list->head;
 
    // add the data to newly created node
    new_node->data  = value;
 
    // This new node is going to be the last node, so make next of it be NULL
    new_node->next = NULL;

    // If the Linked List is empty, then make the new node as head
    if (list->head == NULL)
    {
       list->head = new_node;
       return;
    }

    // If not Empty traverse till the last node
    while (last->next != NULL){
        last = last->next;
    }

    // Insert in the new new node to the end of the linked list
    last->next = new_node;
}

// Insert Value into Linkedlist at specific index
void insertAt(LinkedList *list, int index, int value) {
    // 1. allocate memory to the node
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));
    struct Node *curr = list->head;

    node->data = value;
    node->next = NULL;
    int count = -1;
    while (curr->next != NULL){
        if (index == 0){
            node->next = curr;
            list->head = node;
            break;
        }else{
            if(count < index - 2 || count > index - 2){
                curr = curr->next;
            }else{
                node->next = curr->next;
                curr->next = node;
            }
            count ++;
        }
    }

}

// Delete node at index
void delete(LinkedList *list, int index) {
    if(list->head == NULL){
        return;
    }

    struct Node *node, *temp;

    // Store the head
    temp = list->head;
    int i;


    if(index == 0){
        node =list->head;
        list->head = list->head->next;
        free(node);
        return;
    }

    for(i = 0; temp != NULL && i < index - 1; i++){
        temp = temp->next;
    }

    if(temp == NULL || temp->next == NULL){
        return;
    }

    node = temp->next->next;
    free(temp->next);

    temp->next = node;

}

// Replace value at specific Index of the node
// value - new value that will be used to replace the old value at index
void replace(LinkedList *list, int index, int value) {
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
void EmptyList(LinkedList *list) {


    struct Node *temp_head, *node;

    // Store the head
    temp_head = list->head;
    
    if(list != NULL){
        while (list->head != NULL){
            delete(list, 0);
        }
    }

}
// END LINKEDLIST MODIFICATION FUNCTIONS

// START LINKEDLIST DATA RETRIEVAL FUNCTIONS

// Retrieve the value at the specific Index
int get(LinkedList *list, int index) {
    struct Node *node;
    node = list->head;

    int count = 0;
    while (node != NULL){
        if(count == index){
            return node->data;
        }
        node = node->next;
        count++;
    }
    return -1;
}

// Retrieve the first index of the specific value
int getIndex(LinkedList *list, int value) {
    return getIndexFromSI(list, 0, value);
}

// Retrieve the first index starting from specific index of the linked list
int getIndexFromSI(LinkedList *list, int startindex, int value) {
    if(list->head == NULL){
        return -1;
    }

    struct Node *node;
    node = list->head;

    int index = 0;
    while (node != NULL){
        if(node->data == value && index >= startindex){
            return index;
        }
        node = node->next;
        index++;
    }
    return -1;
}

// Retrieve the Size of the LinkedList
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

// END LINKEDLIST DATA RETRIEVAL FUNCTIONS

// START LINKEDLIST DATA PRINTING FUNCTIONS
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
void printStep(LinkedList *list, int no_of_frames) {

    struct Node *node = list->head;
    int count = 0;
    while (node != NULL) {
        printf("%d\t", node->data);
        node= node->next;
        count++;
    }

    while (count < no_of_frames){
        printf("%d\t", -1);
        count++;
    }
    printf("\n");
}
// END LINKEDLIST DATA PRINTING FUNCTIONS



