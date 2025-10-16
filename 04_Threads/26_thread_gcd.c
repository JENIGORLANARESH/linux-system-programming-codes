#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct numbers{
	int a;
	int b;
};

int gcd(int a, int b){
	while(b != 0){
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

void *gcd_t(void *arg){
	struct numbers *nums = (struct numbers *)arg;
	int a = nums->a;
	int b = nums->b;
	
	int *result = malloc(sizeof(int));

	*result = gcd(a, b);
	pthread_exit(result);
}

int main(void){
	pthread_t thread;
	struct numbers nums;
	printf("Enter a , b : ");
	scanf("%d %d", &nums.a, &nums.b);

	pthread_create(&thread, NULL, gcd_t, &nums);
	
	void *result;

	pthread_join(thread, &result);	

	printf("gcd = %d\n", *(int *)result);
	free(result);
	return 0;
}
