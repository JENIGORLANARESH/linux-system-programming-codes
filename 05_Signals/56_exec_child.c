#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void){
	printf("Exec child : %d, started after execl()\n", getpid());
	printf("Exec child : %d , raising SIGUSR1\n", getpid());
	// here all custom handlers are set to default, so default behavior executes
	raise(SIGUSR1);
	printf("Exec child : %d , finished.\n", getpid());
	return 0;
}
