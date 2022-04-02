#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200
static char *DEV_DRIVER = "/dev/MessageDev";
int main()
{
    int fd, rtn;

    // Input from user that is intended to be
    // stored inside the kernel space
    char input[MAX] = {};
    int options = 0;
    char option[2] = {};
    // Used to store the length of the input string.
	int inputlen = 0;
    
    // Used to store the data 
    // read from the kernel space
    char read_result[100] = {};
    // A flag to check if user wants to input value
    unsigned short int inputFlag = 0; 

    // open the chardev driver
	fd = open(DEV_DRIVER, O_RDWR); 

    // if fail to open the driver (the drive is not in kernel)
	if (fd == -1) 
	{
		perror("Error opening /dev/MessageDev\n");
		exit(EXIT_FAILURE);
	}

	// Successfully open the message dev driver
	printf("Reading from /dev/MessageDev: \n");

	while (1) {
		/* code */
        // To request input from user
        fflush(stdin);
        // scanf('\n');
		printf("Enter a message to be wrriten into device driver. \n");
		fgets(input, MAX, stdin);
        fflush(stdin);
		

		inputlen = strlen(input);
        // write input into the driver
		printf("Writing to /dev/MessageDev: \n"); 
		rtn = write(fd, &input, inputlen);
        // fail to write input
		if (rtn < 0) 
		{
			perror("Error Writing to /dev/MessageDev\n");
		}
        
        printf("Reading from /dev/MessageDev: \n"); 
		rtn = read(fd, &read_result, inputlen);
        // fail to read from kernel
        if (rtn < 0) 
		{
			perror("Error Reading from /dev/MessageDev\n");
		}

        fflush(stdout);

        printf("Message read from kernel : %sNumber of Letters: %d", read_result, inputlen);
        //printf("%d", inputlen);
        printf("\nDo you want to input another message?");
        printf("\nOptions:");
        printf("\n1. Yes \n2. No\n");
        printf("Enter your options : ");
        scanf("\n");
        fgets(option, 3, stdin);
        if((int)*option == 50){
            break;
        }
	}
	exit(EXIT_SUCCESS);
}
