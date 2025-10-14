#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *env[] = {"MYVAR=Hello", "PATH=/bin", NULL};

int main(void){
	printf("Process pid : %d , running\n", getpid());
	
	//execle("/bin/ls", "ls", "-l", NULL, env);

	execle("/usr/bin/env", "env", NULL, env);

	printf("execle failed\n");
	return 0;
}
