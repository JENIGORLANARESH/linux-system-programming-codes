#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	int fds[2];
	int array[] = {3, 2, 1, 5, 7};
	pipe(fds);

	int pid = fork();

	if(pid > 0){
		close(fds[0]);
		printf("Writing array to child\n");
		write(fds[1], array, sizeof(array));
		printf("Wriiten from parent\n");
		close(fds[1]);
		wait(NULL);
	}
	else{
		close(fds[1]);
		printf("Reading from parent \n");
		int arr[5];
		read(fds[0], arr, sizeof(arr));
		printf("Received array for child\n");
		for(int i=0; i<5; i++){
			printf("%d ", arr[i]);
		}
		printf("\n");
		close(fds[1]);
		exit(0);
	}

	return 0;
}
