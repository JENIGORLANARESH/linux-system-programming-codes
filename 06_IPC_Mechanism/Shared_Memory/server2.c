#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

#define SHM_KEY 1234
//server
int main(void){
	int shmid;
	char *shmptr;

	shmid = shmget(SHM_KEY, 1024, IPC_CREAT | 0666);
	if( shmid < 0){
		perror("shmget");
		exit(1);
	}
	shmptr = shmat(shmid, NULL, 0);
	if(shmptr == (char *)-1){
		perror("shmat");
		exit(1);
	}

	shmptr[0] = 0;

	while(1){
		if(shmptr[0] == 1){
			printf("client > %s\n", shmptr+1);
			shmptr[0] = 0;

			printf("Enter message for client : ");
			fgets(shmptr+1, 1023, stdin);
			
			shmptr[0] = 2;
		}
		usleep(100000);
	}


	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
