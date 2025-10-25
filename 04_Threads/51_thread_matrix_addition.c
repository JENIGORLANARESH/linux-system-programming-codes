#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10  

struct matrix_data {
    	int rows;
   	 int cols;
    	int mat1[MAX][MAX];
    	int mat2[MAX][MAX];
    	int result[MAX][MAX];
};

void* add_matrices(void* arg) {
    	struct matrix_data* data = (struct matrix_data*)arg;

    	for (int i = 0; i < data->rows; i++) {
        	for (int j = 0; j < data->cols; j++) {
            		data->result[i][j] = data->mat1[i][j] + data->mat2[i][j];
        	}
    	}

    	printf("Matrix Addition Result:\n");
    	for (int i = 0; i < data->rows; i++) {
        	for (int j = 0; j < data->cols; j++) {
            		printf("%d\t", data->result[i][j]);
        	}
        	printf("\n");
    	}

    	pthread_exit(NULL);
}

int main() {
    	pthread_t thread;
    	struct matrix_data data;

    	printf("Enter number of rows : ");
    	scanf("%d", &data.rows);
    	printf("Enter number of columns : ");
    	scanf("%d", &data.cols);

    	printf("Enter Mat 1:\n");
    	for (int i = 0; i < data.rows; i++)
            for (int j = 0; j < data.cols; j++)
            	scanf("%d", &data.mat1[i][j]);
    	printf("Enter mat2 : \n");
    	for (int i = 0; i < data.rows; i++)
            for (int j = 0; j < data.cols; j++)
            	scanf("%d", &data.mat2[i][j]);

    	if (pthread_create(&thread, NULL, add_matrices, &data) != 0) {
        	perror("Failed to create thread");
        	return 1;
    	}
    	pthread_join(thread, NULL);
    	return 0;
}

