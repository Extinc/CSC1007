//
// Created by LIM KEI YIANG on 22/2/22.
//

#include <unistd.h>
#include "OptimalPageReplacement.h"
void OptimalPageReplacement(LinkedList *data, int no_of_frames)
{
    struct Node *temp = data->head;
    LinkedList *memframe = malloc(sizeof(LinkedList));
    memframe->head = NULL;
    int i, pageval, fault_count = 0;
    int size, exist;
    int index_replace, replace_val; // Value to be replaced
    int currentidx = 0;
    int replace_flag;

    while (temp != NULL)
    {
        pageval = temp->data;
        replace_flag = -1;
        index_replace = -1;
        // Search for the value to check if it exist in the Memory Frame
        exist = getIndex(memframe, pageval);
        if (exist == -1) // Value does not exist in memory
        {
            // Get the size of memory frame filled
            size = getSize(memframe);
            if (size < no_of_frames)
            {
                // When it is not full and contains a value check if value exist
                insert(memframe, pageval);

                // To Print the Step of the Page Fault
                printf("STEP %d\t:\t", fault_count + 1);
                printStep(memframe, no_of_frames);
            }
            else // when frames alr filled up
            {

                for (i=0; i< no_of_frames;i++){
                    int value_check = get(memframe, i);
                    // Check if value inside memory frame exist in the future
                    exist = getIndexFromSI(data, currentidx, value_check);
                    // Value does not exist in the future
                    if(exist == -1 || exist < currentidx){
                        replace(memframe, i, pageval);

                        replace_flag = 1;
                        break;
                    }else{

                        if(index_replace == -1){
                            index_replace = exist;
                            replace_val = value_check;
                        }else{
//                            printf("EXIST %d : %d \t val: %d\n", exist, index_replace, value_check);
                            if(exist > index_replace){
                                index_replace = exist;
                                replace_val = value_check;
                            }
                        }
                    }
                }
                if(replace_flag == -1){
                    replace(memframe, getIndex(memframe, replace_val), pageval);

                }

                // To Print the Step of the Page Fault
                printf("STEP %d\t:\t", fault_count + 1);
                printStep(memframe, no_of_frames);
            }
            fault_count++;
        }
        temp = temp->next;
        currentidx++;
    }
    printf("\n");
    printf("There are %d page faults in this page replacement process", fault_count);

    temp = NULL; // UNLINK
    EmptyList(memframe);
    free(memframe);
}