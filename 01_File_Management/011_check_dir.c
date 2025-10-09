#include <stdio.h>
#include <sys/stat.h>

int main(void){
	char dir[50];
	printf("Enter directory : ");
	scanf("%49s", dir);

	struct stat st;

	if( stat(dir, &st) == 0){
		if(S_ISDIR(st.st_mode)){
			printf("Directory %s exits\n", dir);
		}
		else{
			printf("%s exists but not a directory\n", dir);
		}
	}
	else{
		perror("stat");
		printf("%s does not exists\n", dir);
	}
	return 0;
}
