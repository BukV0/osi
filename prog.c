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
        // rewrite the KeyboardInterrupt signal handler
   signal(SIGINT,interrupt_handler);

    char filename[256]; 
    // file name parameter
    char template[256];
    while(1){
    template[0] = 'f';
    template[1] = ' ';
    get_correct_file_name(&filename);
    int k = Search_in_File(filename,template);
    printf("a.c pid %d\n",getpid());
    char *argg[] = {arr,NULL};
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
