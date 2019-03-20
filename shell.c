#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h> 
#define MAXLINE 80 /* The maximum length command */
int main(void){
	char buffer[MAXLINE/2 + 1];
	char *args[MAXLINE/2 + 1]; /* command line arguments */
	int shouldrun = 1; /* flag to determine when to exit program */
	char *token,*command;
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
			command=strdup(token);
                        args[0]=strdup(command);
			count=1;
			while(token != NULL){
				args[count]=strdup(token);
				count++;
				token = strtok(NULL, " ");
			}
			args[count]="\0";
			if(strcmp(args[0], "exit") == 0){
				int doexit = 1;
				exit(1);
  			}
			int result =execvp(command,args);
			if(result < 0){
				printf("*** ERROR: exec failed\n");
        			exit(1);
      			}	
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
