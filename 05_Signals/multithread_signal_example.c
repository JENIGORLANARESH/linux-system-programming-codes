#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

void handle_signal(int sig){
	printf("cuaght signal......\n");
}

void *thread_signal_waiter(void *arg){
	sigset_t *set = (sigset_t *)arg;
	int sig;
	while(1){
		if(sigwait(set, &sig) == 0){
			printf("signal waiter received signal : %d\n", sig);
			handle_signal(sig);
		}
		else{
			perror("sigwait");
			exit(1);
		}
	}
	return NULL;
}

void *thread_worker(void *arg){
	while(1){
		printf("worker thread is running..\n");
		sleep(2);
	}
	return NULL;
}

int main(void){
	pthread_t worker, signal_waiter;
	sigset_t set;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	//sigaddset(&set, SIGTERM);
	
	int ret = pthread_sigmask(SIG_BLOCK, &set, NULL); // how, newset, oldset
	if(ret != 0){
		perror("pthread_sigmask");
		exit(1);
	}

	pthread_create(&worker, NULL, thread_worker, NULL);
	pthread_create(&signal_waiter, NULL, thread_signal_waiter, (void *)&set);

	pthread_join(worker, NULL);
	pthread_join(signal_waiter, NULL);

	return 0;
}
