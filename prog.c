#include<stdio.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define NO_PARAMETERS_ERROR 1
#define NOT_FOUND_ERROR 2
#define CANT_OPEN_ERROR 3


int interrupt_counter = 0;
void interrupt_handler()       // handler of keyboard interrupt signal
{
    interrupt_counter++;       // increase the counter of keybo.ard interruptions
    if (interrupt_counter >=10)
    {
        exit(1); // finish program
    }
}
void get_correct_file_name(char* filename){
    while (1){
        memset(filename, 0, 256);   // null filename
        printf("\nEnter filename: ");
        scanf("%s", filename);
        if (access(filename, F_OK)) // check that file filename is exists. If no, quit
        {
            printf("\nFile \"%s\" not found\n", filename);
        } else {
            return;
        }
    }
}


int main(int argc, char** argv){
        // rewrite the KeyboardInterrupt signal handler
   signal(SIGINT,interrupt_handler);
    char filename[256];                                // file name parameter

    get_correct_file_name(&filename);

}
