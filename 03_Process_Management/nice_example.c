#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/resource.h>

//Higher nice value → process gets less CPU time.
//Lower nice value → process gets more CPU time.

int main(void){
	pid_t pid1, pid2;
	
	pid1 = fork();
	if(pid1 == 0){
		printf("child1 priority = %d\n", getpriority(PRIO_PROCESS, 0));
//		nice(5);
		nice(100);
		printf("After : child1 has nice = %d\n", getpriority(PRIO_PROCESS, 0));
		for(int i=0; i<1000000000; i++);
		printf("child1 finished\n");
		exit(0);
	}
	pid2 = fork();
	if(pid2 == 0){
		printf("child2 priority = %d\n", getpriority(PRIO_PROCESS, 0));
//		nice(-5);
		nice(5);
		printf("After : child2 has nice = %d\n", getpriority(PRIO_PROCESS, 0));
		for(int i=0; i<1000000000; i++);
		printf("child2 finished\n");
		exit(0);
	}

	wait(NULL);
	wait(NULL);
	printf("parent pid = %d , nicevalue = %d\n", getpid(), getpriority(PRIO_PROCESS, 0));

	return 0;
}
