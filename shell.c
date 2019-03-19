#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h> 
#define MAXLINE 80 /* The maximum length command */
int main(void){
	char buffer[MAXLINE/2 + 1];
	char *args[MAXLINE/2 + 1]; /* command line arguments */
	int shouldrun = 1; /* flag to determine when to exit program */
	char *token;
	int count;
	while (shouldrun){
		printf("osh>");
		fflush(stdout);
		if (fgets(buffer, sizeof(buffer), stdin) == NULL){ 
			break; 
		}
		pid_t pid;
        	pid=fork();
        	if(pid==0){
                	token=strtok(buffer, " ");
			count=0;
			while(token != NULL){
				args[count++]=token;
				token = strtok(NULL, " ");
			}
			execvp(args[0],args);	
        	}
        	else if(pid>0){
                	int a=50;
                	wait(&a);
        	}
		else{
			printf("Fork failed");	
		}
		
	}
	return 0;
}
