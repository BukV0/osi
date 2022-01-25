#include<stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define CANT_OPEN_ERROR 3

int main(int argc, char* argv[]){
    //printf("%d", argc);
    printf("test.c pid %d\n",getpid());
     FILE* file;                                              // file descriptor
        if ((file=fopen("info.txt", "w"))==NULL)                 // open file for write. If it isn't exist, create
        {
            fprintf(stderr, "Can't open file info.txt");         // if file is not accesseble, quit
            exit(CANT_OPEN_ERROR);
        }
        else
        {
            for(int i = 0;i <argc;i++){
            fprintf(file, argv[i]);
            fprintf(file, "\n");
            } // if file is accesseble, rewrite information in it to our
            fclose(file);
        }

    return 0;
}
