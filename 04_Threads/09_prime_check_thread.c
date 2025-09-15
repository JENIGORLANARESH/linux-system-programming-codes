#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *prime(void *arg){
	int n = *(int *)arg;
	int isPrime = 1;
	if(n <= 1){
		isPrime = 0;
	}
	else{
		for(int i=2; i*i <= n; i++){
			if( (n % i) == 0){
				isPrime = 0;
				break;
			}
		}
	}

	if(isPrime){
		printf("%d is Prime\n", n);
	}
	else
		printf("%d is Not Prime\n", n);
	return NULL;
}

int main(void){
	pthread_t t1;
	int n;
	printf("Enter n : ");
	scanf("%d", &n);

	if( pthread_create(&t1, NULL, prime, &n) != 0){
		perror("pthread_create failed");
		return 1;
	}
	pthread_join(t1, NULL);
	return 0;
}
