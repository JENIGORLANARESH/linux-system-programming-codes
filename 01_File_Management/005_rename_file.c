#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void){
	char oldname[50], newname[50];
	printf("Enter oldname : ");
	scanf("%s", oldname);
	printf("Enter newname : ");
	scanf("%s", newname);

	struct stat fileStat;

	int ret = stat(oldname, &fileStat);
	if(ret != 0){
		perror(oldname);
		exit(1);
	}

	if( rename(oldname, newname) == 0){
		printf("Renamed successfully\n");
	}
	else{
		perror("Unsuccessfull");
	}
	
	return 0;
}
