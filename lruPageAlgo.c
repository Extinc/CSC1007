//
// Created by LIM KEI YIANG on 20/2/22.
//

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#define MAX 200

void LRUPageReplacement(char *data, int fsize, int capacity);
short contains(int *data, int datasize, int value);
int main();
int main() {
    char size[MAX] =  {};
    char *refStr = size;
    int frameSize = 0;
    printf("Enter the numbers for page replacement Algorithm : ");
    fgets(refStr, sizeof(size), stdin);
    fflush(stdin);

    printf("Enter the number of Frames : ");
    scanf("%d", &frameSize);
   // printf("%s", refStr);
    //printf("\n%s", size);
    LRUPageReplacement(refStr, frameSize, 200);
    return 0;
}

void LRUPageReplacement(char *data, int fsize, int capacity) {
    int page_faults = 0;
    //int page_mem[MAX] =  {};
    int *ptr_page = malloc(sizeof(int) * fsize);
    int i,j;
    int flag = 0;
    int occur[10] = {};
    //printf("%d", sizeof(data));
    printf("%d", strlen(data));

    // Initialize page to -1
    for(i = 0; i < fsize; i++){
        *(ptr_page + i) = -1;
    }

    for(i = 0; i< capacity; i++){
        // If the value is from 0 - 9 for each char
        if(*(data + i) >= 48 && *(data + i) <= 57){
            int tempval = (int) *(data + i);
            if(contains(&ptr_page, fsize, tempval) == 1){
                flag = 1;
                // If page contains the values
                printf("TEST : %h",contains(&ptr_page, fsize, tempval));
                break;
            }else{
                if(contains(&ptr_page, fsize, tempval) == -1){
                    // If the page have space
                }else{
                    // If the page does not have space
                }
            }
        }
    }

    free(ptr_page);
}

// 0 : Value is not within the array
// 1 : Value is within the array
short contains(int *data, int datasize, int value) {
    int i;
    short contain = 0;
    for(i = 0; i < datasize; i++){
        if((int)*(data+i) == value){
            contain = 1;
            break;
        }
    }
    return contain;
}

