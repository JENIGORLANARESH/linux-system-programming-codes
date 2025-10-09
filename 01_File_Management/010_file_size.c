#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void){
	char filename[50];
	printf("Enter a filename : ");
	scanf("%49s", filename);

	struct stat st;

	int St = stat(filename, &st);

	if(St == 0){
		printf("size = %ld\n", st.st_size);
	}
	else{
		perror("Error");
		exit(1);
	}

	return 0;
}
