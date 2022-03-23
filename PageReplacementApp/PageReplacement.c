//
// Created by LIM KEI YIANG on 22/2/22.
//

#include "PageReplacement.h"

void LRUPageReplacement(LinkedList *data, int no_of_frames) {
    struct Node *temp = data->head;
    LinkedList *LRU = malloc(sizeof(LinkedList)); // To store and check for Least Recently Used
    LinkedList *memframe = malloc(sizeof(LinkedList));
    LRU->head = NULL;
    memframe->head = NULL;
    int pageval, fault_count = 0;
    int size, exist;
    int i = 0;

    // Loop through the LINKEDLIST
    while (temp != NULL){
        pageval = temp->data;

        // Search for the value to check if it exist in the Memory Frame
        exist = getIndex(memframe, pageval);
        if(exist == -1){
            // Value does not exist in memory
            // Get the size of memory frame filled
            size = getSize(memframe);
            if(size < no_of_frames){
                // When it is not full and contains a value check if value exist
                insert(memframe, pageval);
                insert(LRU, pageval);

                // To Print the Step of the Page Fault
                printf("STEP %d\t:\t", fault_count + 1);
                printStep(memframe, no_of_frames);
            }else{
                // WHen frames have been filled up to maximum

                int indexofobj = getIndex(memframe, get(LRU,0));

                // Replace the value at the page with Least Recently Used in the Memory
                replace(memframe, indexofobj, pageval);

                // Get the First Value in the LRU LINKEDLIST and delete it
                // Then Insert the new page value at the end of the LINKEDLISt
                indexofobj = getIndex(LRU, get(LRU,0));
                delete(LRU,indexofobj);
                insert(LRU, pageval);

                // To Print the Step of the Page Fault
                printf("STEP %d\t:\t", fault_count + 1);
                printStep(memframe, no_of_frames);
            }
            fault_count++;
        }else{
            // If value exist in memory

            // Change the Order Of the LEAST RECENTLY USED LINKEDLIST
            delete(LRU,getIndex(LRU, pageval));
            insert(LRU, pageval);
        }
        i++;
        temp = temp->next;
    }


    printf("\n");
    printf("There are %d page faults in this page replacement process",fault_count);
    temp = NULL;// UNLINK
    EmptyList(LRU);
    EmptyList(memframe);
    free(LRU);
    free(memframe);
}




