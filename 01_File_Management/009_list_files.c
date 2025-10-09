#include <stdio.h>
#include <stdlib.h>

#include <dirent.h> 	// opendir , readdir , closedir

int main(void){
	DIR *dir;
	struct dirent *entry;

	dir = opendir(".");	// current directory
	
	if(dir == NULL){
		perror("Error in opening");
		exit(1);
	}

	printf("Files in current folder \n");

	while( (entry = readdir(dir)) != NULL){
		printf("%s\n", entry->d_name);
	}

	closedir(dir);

	return 0;
}
