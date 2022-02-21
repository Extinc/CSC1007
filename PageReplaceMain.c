//
// Created by LIM KEI YIANG on 20/2/22.
//

#include "string.h"
#include "LinkedList.h"
#define MAX 200

void LRUPageReplacement(LinkedList *data, int fsize);
int main();
int main() {
    char size[MAX] =  {};
    char *refStr = size;
    int reflist[30] = {};
    int options = 0;
    int no_of_frames = 0, i;
    LinkedList *refll = malloc(sizeof(LinkedList));
    printf("Please choose a Page Replacement Algorithm\n");
    printf("Options: \n");
    printf("\t1. First in first out (FIFO) page replacement algorithm\n");
    printf("\t2. Optimal page replacement algorithm\n");
    printf("\t3. Least recently used (LRU) page replacement algorithm\n");
    printf("Enter the options (1, 2 or 3):");

    scanf("%d", &options);
    fflush(stdin);

    printf("Enter the number of Frames : \n");
    scanf("%d", &no_of_frames);
    fflush(stdin);

    printf("Enter the reference list : ");
    fgets(refStr, sizeof(size), stdin);

    for(i = 0; i < strlen(refStr); i++){
        if(*(refStr + i) >= 48 && *(refStr + i) <= 57) {
            insert(refll,(int) (*(refStr + i) - '0'));
        }
    }


    LRUPageReplacement(refll, no_of_frames);
    EmptyList(refll);

    free(refll);
    return 0;
}

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
                printf("STEP %d :\t", fault_count);
                insert(LRU, pageval);
                printStep(memframe, fsize);
            }else{
                // WHen frames have been filled up to maximum
                int indexofobj = getIndex(memframe, get(LRU,0));
                replace(memframe, pageval, indexofobj);

                printf("STEP %d :\t", fault_count);
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
    EmptyList(memframe);
    free(memframe);
}




