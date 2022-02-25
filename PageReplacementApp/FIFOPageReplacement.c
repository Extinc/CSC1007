//
// Created by LIM KEI YIANG on 22/2/22.
//

#include "FIFOPageReplacement.h"

void FIFOPageReplacement(LinkedList *data, int fsize) {
    struct Node *temp = data->head;
    LinkedList *memframe = malloc(sizeof(LinkedList)); // memory frame
    int FI = 0; // To store and check for First
    int pageval, fault_count = 0; //page value, total fault
    int size, exist; //size of frame, if the thing exist
    
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
                printf("STEP %d\t:\t", fault_count + 1);
                printStep(memframe, fsize);
            }else{
                // WHen frames have been filled up to maximum
                replace(memframe,FI, pageval);
                printf("STEP %d :\t", fault_count + 1);
                printStep(memframe, fsize);
                if (FI < 3){
                    FI++;
                } else{
                    FI =0;
                }
            }
            fault_count++;
        }else{
            // If value exist in memory
        }
        
        temp = temp->next;
    }


    printf("\n");
    printf("Number of Fault : %d ",fault_count);
    temp = NULL;// UNLINK
    EmptyList(memframe);
    free(memframe);
}