#include<stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define NO_PARAMETERS_ERROR 1
#define NOT_FOUND_ERROR 2
#define CANT_OPEN_ERROR 3

char* arr;
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
            //printf("okey");
            return;
        }
        //printf("okettty");
    }
}


void add_into_array(char *str,int fns){
    if(fns == 1){
        arr = (char *)malloc(256);
        strcpy(arr,str);
        return;
    }
    else{ 
        arr = (char *)realloc(arr,256*fns);
        strcat(arr,str);
        return;
    }
}


int Search_in_File(char *fname, char *str) {
	FILE *fp = fopen(fname, "r");
	int line_num = 1;
	int find_result = 0;
	char temp[256];
	while(fgets(temp, 256, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			find_result++;
            add_into_array(temp,find_result);
		}
		line_num++;
	}

	if(find_result == 0) {
		printf("\nSorry, couldn't find a match.\n");
	}
	
	if(fp) {
		fclose(fp);
	}
   	return(0);
}

int main(){
    signal(SIGINT,interrupt_handler);
    char filename[256]; 
    char template[256];
    template[0] = 'e';
    template[1] = 'w';
    get_correct_file_name(&filename);
    int pipe_descriptors[2];                           // pipe IN/OUT descriptors
    pipe(pipe_descriptors); 
     if (fork() == 0)                                   // make parallel process
    {
        // child process
        // we perform some actions in it
        close(pipe_descriptors[0]);  // close pipe IN descriptor in child process because there is no need in it
        close(1);                    // close STDOUT descriptors
        dup2(pipe_descriptors[1], 1);// copy pipe OUT descriptor into the STDOUT place. All STDOUT information will be in pipe.

        printf("%d\n", 0);           // beautifier
        execl("/usr/bin/grep",  "grep",template, filename, 0);
    }
    else
    {
        wait();                                                  // wait untill child process die
        int fns = 0;
        char buffer[256];                                       // information buffer
        memset(&buffer, 0, 256);
        ssize_t numRead;
        //dup2(1,pipe_descriptors[1]);
        read(pipe_descriptors[0], buffer, 256);
        // while (1) {
        //          numRead = read(pipe_descriptors[0], buffer, 256);
        //         if (numRead == -1) {
        //             perror("read");
        //             exit(EXIT_FAILURE);
        //         }
        //         if (numRead == 0){
        //             break;
        //         }
        //         fns++;
        //         add_into_array(buffer,fns);
        // }
        //char *argg[] = {arr,NULL};
        char *argg[] = {buffer,NULL};
        execv("./tes",argg);
    }

}


/*
memset
scanf
printf
strstr
malloc
realloc
execv
signal
SIGINT
fopen
fclose
strcpy
sctrcat
access
exit
fprinf
stderr
*/
