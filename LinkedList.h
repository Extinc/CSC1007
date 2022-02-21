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
void printList(struct Node *head);
#endif //OSPROJ_LINKEDLIST_H
