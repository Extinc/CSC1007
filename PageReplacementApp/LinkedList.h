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
    struct Node *tail;
}LinkedList;

void delete(LinkedList *list, int pos);
void insert(LinkedList *list, int value);
void insertAt(LinkedList *list, int pos, int value);
void replace(LinkedList *list, int value, int index);
int isEmpty(struct Node *head);
void EmptyList(LinkedList *list); // Used to Empty & free all the nodes
int search(LinkedList *list, int searchval); //  Search function
int getSize(LinkedList *list); //  Size of LinkedList
int get(LinkedList *list, int pos);
int getIndex(LinkedList *list, int value);

void printList(LinkedList *list);
void printStep(LinkedList *list, int framesize);
#endif //OSPROJ_LINKEDLIST_H
