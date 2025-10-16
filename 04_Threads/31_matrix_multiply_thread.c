#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ROW 3
#define COL 3

struct matrices{
	int A[ROW][COL];
	int B[ROW][COL];
	int C[ROW][COL];
};

void *multiply(void *arg){
	struct matrices *m = (struct matrices *)arg;
	for(int i=0; i<ROW; i++){
		for(int j=0; j<COL; j++){
			m->C[i][j] = 0;
			for(int k=0; k<COL; k++){
				m->C[i][j] = m->C[i][j] + m->A[i][k] * m->B[k][j];
			}
		}
	}
	pthread_exit(NULL);
}

int main(void){
	pthread_t pid;
	struct matrices m;
	printf("Enter elements for matrix A %d * %d : \n", ROW, COL);
	for(int i=0; i<ROW; i++){
		for(int j=0; j<COL; j++){
			scanf("%d", &m.A[i][j]);
		}
	}
	printf("Enter elements for matrix B %d * %d : \n", ROW, COL);
	for(int i=0; i<ROW; i++){
		for(int j=0; j<COL; j++){
			scanf("%d", &m.B[i][j]);
		}
	}

	pthread_create(&pid, NULL, multiply, &m);

	pthread_join(pid, NULL);

	printf("Resultant : \n");
	for(int i=0; i<ROW; i++){
		for(int j=0; j<COL; j++){
			printf("%d ", m.C[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}
