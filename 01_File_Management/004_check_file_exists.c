#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void){
	char filename[50];
	printf("Enter filename : ");
	scanf("%49s", filename);

	struct stat fileStat;

	int ret = stat(filename, &fileStat);

	if(ret == 0){
		printf("File exists\n");
	}
	else{
		perror("stat");
		exit(1);
	}

	return 0;
}
