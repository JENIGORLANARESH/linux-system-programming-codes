#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct rectangle {
	double length;
    	double width;
};

void* calculate_area(void* arg) {
	struct rectangle* rect = (struct rectangle*)arg;
    	double area = rect->length * rect->width;

    	printf("Length: %.2f, Width: %.2f\n", rect->length, rect->width);
    	printf("Area of Rectangle: %.2f\n", area);

    	pthread_exit(NULL);
}

int main() {
    	pthread_t thread;
    	struct rectangle rect;

    	printf("Enter length ");
    	scanf("%lf", &rect.length);
   	printf("Enter width ");
    	scanf("%lf", &rect.width);

    	if (pthread_create(&thread, NULL, calculate_area, &rect) != 0) {
        	perror("create thread");
        	return 1;
    	}
    	pthread_join(thread, NULL);
    	return 0;
}

