#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void){
	char dir[50];
	printf("Enter parent directory name : ");
	scanf("%49s", dir);
	char path[50] = "../";
	strcat(path, dir);

	if( mkdir(path, 0755) == 0){
		printf("Parent directory created successfully\n");
	}
	else{
		perror("mkdir");
	}

	return 0;
}
