#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	// unlink

int main(void){
	char filename[50];
	printf("Enter filename : ");
	scanf("%49s", filename);

	int ret = unlink(filename);

	if(ret == 0){
		printf("Successfully deleted\n");
	}
	else{
		perror("Delete failed");
		exit(1);
	}

	return 0;
}
