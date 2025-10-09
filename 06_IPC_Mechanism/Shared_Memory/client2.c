#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

#define SHM_KEY 1234

int main(void){
	int shmid;
	char *shmptr;

	shmid = shmget(SHM_KEY, 1024, 0);
	if(shmid < 0){
		perror("shmid");
		exit(1);
	}
	shmptr = shmat(shmid, NULL, 0);
	if(shmptr == (char *)-1){
		perror("shmptr");
		exit(1);
	}
	
	while(1){
		if(shmptr[0] == 0){
			printf("Enter message to server : ");
			fgets(shmptr+1, 1023, stdin);
			shmptr[0] = 1;
		}
		if(shmptr[0] == 2){
			printf("Server > %s\n", shmptr+1);
			shmptr[0] = 0;
		}
		usleep(100000);
	}

	shmdt(shmptr);
	return 0;
}
