#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main(void){
	int *shmids;
	int memories;
	int size;
	key_t key;

	printf("Enter no of shared memories : ");
	scanf("%d", &memories);

	shmids = (int *)malloc(memories * sizeof(int));

	for(int i=0; i<memories; i++){
		printf("Enter size of shared memory %d : \n", i+1);
		scanf("%d", &size);
		printf("Enter key of shared memory %d : \n", i+1);
		scanf("%i", &key);
		shmids[i] = shmget(key, size, IPC_CREAT | 0666);
		if(shmids[i] < 0){
			perror("shmids");
			exit(1);
		}
		printf("memory %d created : shmid : %d, key : %i, size : %d\n", i+1, shmids[i], key, size);
	}

	for(int i=0; i<memories; i++){
		shmctl(shmids[i], IPC_RMID, NULL);
	}
	free(shmids);
	
	printf("all shared memories removed\n");
	printf("freed dynamically allocated memory\n");
	return 0;
}
