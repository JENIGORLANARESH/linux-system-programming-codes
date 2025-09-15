#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct Numbers{
	int a;
	int b;
};

void *sum(void *arg){
	struct Numbers *nums = (struct Numbers *)arg;
	int sum = nums->a + nums->b;
	printf("Sum = %d\n", sum);
	return NULL;
}

int main(void){
	pthread_t t1;
	struct Numbers nums;
	printf("Enter a : ");
	scanf("%d", &nums.a);
	printf("Enter b : ");
	scanf("%d", &nums.b);

	pthread_create(&t1, NULL, sum, &nums);

	pthread_join(t1, NULL);
	return 0;
}
