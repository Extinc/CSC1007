//
// Created by LIM KEI YIANG on 21/2/22.
//

#ifndef OSPROJ_LINKEDLIST_H
#define OSPROJ_LINKEDLIST_H

#include<stdio.h>
#include<stdlib.h>
struct Node{
    int data;
    struct Node *next;
};

typedef struct {
    struct Node *head;
}LinkedList;

//Insert Value into LinkedList at the end
void insert(LinkedList *list, int value);

// Insert Value into Linkedlist at specific index
void insertAt(LinkedList *list, int index, int value);

// Delete node at index
void delete(LinkedList *list, int index);

// Replace value at specific Index of the node
// value - new value that will be used to replace the old value at index
void replace(LinkedList *list, int index, int value);

// Used to Empty & free all the nodes
void EmptyList(LinkedList *list);

// Get the Size of LinkedList
int getSize(LinkedList *list);

// Get the value at a specific index within the LinkedList
int get(LinkedList *list, int index);

// Get the first index of specific value
int getIndex(LinkedList *list, int value);

// Get the first index from linkedlist with specifc starting index
int getIndexFromSI(LinkedList *list, int startindex, int value);

// printList is used to print the List
void printList(LinkedList *list);

// used to printstep for the page replacement algorithm
void printStep(LinkedList *list, int no_of_frames);

#endif //OSPROJ_LINKEDLIST_H
