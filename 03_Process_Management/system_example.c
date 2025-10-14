#include <stdio.h>
#include <stdlib.h>

int main(void){
	int ret;

	printf("Executing ls -l\n");
	ret = system("ls -l");
	if(ret == -1){
		perror("system()");
		exit(1);
	}

	printf("executing pwd \n");
	ret = system("pwd");
	if(ret == -1){
		perror("system pwd");
		exit(1);
	}

	return 0;
}
