#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char **env;

int main(void){
	char *args[] = {"/bin/ls", "-l", NULL};
	printf("Before execvp\n");
	int ret = execve("/bin/ls", args, env);
	if(ret == -1){
		perror("execve");
		exit(1);
	}
	printf("Wont execute if execvp successfull\n");
	return 0;
}
