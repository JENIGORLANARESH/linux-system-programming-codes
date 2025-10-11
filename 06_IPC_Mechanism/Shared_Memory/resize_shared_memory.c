#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

int main(void){
	int oldshm, newshm;
	char *oldptr, *newptr;
	key_t key;
	int oldsize, newsize;

	printf("Enter old shm key : ");
	scanf("%i", &key);
	printf("Enter old size : ");
	scanf("%d", &oldsize);

	oldshm = shmget(key, oldsize, 0666);
	if(oldshm < 0){
		perror("oldshmget");
		printf("shared memory with key %i not present\n", key);
		exit(1);
	}
	oldptr = shmat(oldshm, NULL, 0);
	if(oldptr == (char *)-1){
		perror("old shmat");
		exit(1);
	}

	printf("Current contents of shared memory : %s\n", oldptr);

	printf("Enter new shared memory size : ");
	scanf("%d", &newsize);

	newshm = shmget(IPC_PRIVATE, newsize, IPC_CREAT | 0666);
	if(newshm < 0){
		perror("new shmget");
		exit(1);
	}
	newptr = shmat(newshm, NULL, 0);
	if(newptr == (char *)-1){
		perror("new shmat");
		exit(1);
	}

	if(oldsize < newsize){
		strncpy(newptr, oldptr, oldsize);
	}
	else{
		strncpy(newptr, oldptr, newsize);
	}

	shmdt(oldptr);
	shmctl(oldshm, IPC_RMID, NULL);

	printf("old shared memory resized successfully\n");
	printf("New shmid : %d , contents : %s\n", newshm, newptr);

	printf("Enter new contents : ");
	getchar();
	fgets(newptr, newsize, stdin);
	newptr[strcspn(newptr, "\n")] = '\0';
	printf("New contents of shm : %s\n", newptr);

	shmdt(newptr);
	shmctl(newshm, IPC_RMID, NULL);

	return 0;
}
