//
// Created by LIM KEI YIANG on 22/2/22.
//

#include "PageReplacement.h"

void LRUPageReplacement(LinkedList *data, int fsize) {
    struct Node *temp = data->head;
    LinkedList *LRU = malloc(sizeof(LinkedList)); // To store and check for Least Recently Used
    LinkedList *memframe = malloc(sizeof(LinkedList));
    int i, pageval, fault_count = 0;
    int size, exist;
    i = 0;
    while (temp != NULL){
        pageval = temp->data;

        exist = search(memframe, pageval);
        if(exist == -1){
            // Value does not exist in memory
            // Get the size of memory frame filled
            size = getSize(memframe);
            if(size < fsize){
                // When it is not full and contains a value check if value exist
                insert(memframe, pageval);
                printf("STEP %d :\t", fault_count + 1);
                insert(LRU, pageval);
                printStep(memframe, fsize);
            }else{
                // WHen frames have been filled up to maximum
                int indexofobj = getIndex(memframe, get(LRU,0));
                replace(memframe, pageval, indexofobj);

                printf("STEP %d :\t", fault_count + 1);
                indexofobj = getIndex(LRU, get(LRU,0));
                delete(LRU,indexofobj);
                insert(LRU, pageval);
                printStep(memframe, fsize);
            }
            fault_count++;
        }else{
            // If value exist in memory
            delete(LRU,getIndex(LRU, pageval));
            insert(LRU, pageval);
        }
        i++;
        temp = temp->next;
    }


    printf("\n");
    printf("Number of Fault : %d ",fault_count);
    temp = NULL;// UNLINK
    EmptyList(LRU);
    EmptyList(memframe);
    free(memframe);
}




