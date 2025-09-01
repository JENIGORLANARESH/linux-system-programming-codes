#include <stdio.h>
#include <stdlib.h>	// exit

int main(void){
	char srcname[50];
	char dstname[50];
	printf("Enter source file : ");
	scanf("%49s", srcname);
	printf("Enter destination : ");
	scanf("%49s", dstname);

	if( rename(srcname, dstname) == 0){
		printf("Successfully moved from %s : %s\n", srcname, dstname);
	}
	else{
		perror("Failed to move");
		exit(1);
	}

	return 0;
}
