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
   //signal(SIGINT,interrupt_handler);
    char filename[256];                                // file name parameter

    get_correct_file_name(&filename);

    int pipe_descriptors[2];                           // pipe IN/OUT descriptors
    pipe(pipe_descriptors);                            // init pipe

    if (fork() == 0)                                   // make parallel process
    {
        // child process
        // we perform some actions in it
        close(pipe_descriptors[0]);  // close pipe IN descriptor in child process because there is no need in it
        close(1);                    // close STDOUT descriptors
        dup2(pipe_descriptors[1], 1);// copy pipe OUT descriptor into the STDOUT place. All STDOUT information will be in pipe.

        printf("%d\n", 0);           // beautifier
        execl("/usr/bin/wc",  "wc",  filename, 0); // we need info about rows, words and bytes in file
    }
    else
    {
        wait();                                                  // wait untill child process die

        char buffer[1000];                                       // information buffer
        memset(&buffer, 0, 1000);                                // null the buffer memory
        read(pipe_descriptors[0], buffer, 1000);                 // read info from pipe IN channel

        int words = 0;                                           // Words counter
        sscanf(buffer, "%*d %d", &words);                        // parse info from buffer into counter
        printf("Count WORDS in FILE %s: %d\n", filename, words); // print results

        FILE* file;                                              // file descriptor
        if ((file=fopen("info.txt", "w"))==NULL)                 // open file for write. If it isn't exist, create
        {
            fprintf(stderr, "Can't open file info.txt");         // if file is not accesseble, quit
            exit(CANT_OPEN_ERROR);
        }
        else
        {
            fprintf(file, "Count WORDS in FILE %s: %d\n", filename, words); // if file is accesseble, rewrite information in it to our
            fclose(file);
        }
        while(getchar() != 'q') // infitite cycle to catch KeyboardInterrupt signals
        {
        }

        printf("FINISHED\n");
    }
}