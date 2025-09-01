#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void){
	
	int status = mkdir("File", 0755);

	if(status == -1){
		perror("creation failed");
		exit(1);
	}

	printf("Directory created successfully\n");
	return 0;
}
