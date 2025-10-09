#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void){
	char command[20];
	char *args[4];
	int id, stat;
	while(1){
		printf("myshell>");
		fgets(command, sizeof(command), stdin);
		command[strcspn(command, "\n")] = '\0';
		
		/*	
		if(strncmp(command, "ver", 3) == 0){
			printf("Versiong.2.3.3 12/03/2023\n");
			continue;
		}
		*/	
		if(strcmp(command, "exit") == 0){
			exit(5);
		}

		args[0] = command;
		args[1] = NULL;
		id = fork();
		if(id == 0){
			execvp(command, args);
			exit(5);
		}
		wait(&stat);
		printf("child process with pid = %d terminated\n", id);
	}
	return 0;
}
