#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main(void){
	struct shmid_ds buf;
	int possible_shms = 1000;

	printf("Usage statistics\n");
	printf("SHMID\tKEY\t\tSIZE\tATTACHES\n");
	for(int i=0; i<possible_shms; i++){
		if( shmctl(i, IPC_STAT, &buf) == 0){
			printf("%d\t%i\t\t%ld\t%ld\n", i, buf.shm_perm.__key, buf.shm_segsz, buf.shm_nattch);
		}
	}
	return 0;
}
