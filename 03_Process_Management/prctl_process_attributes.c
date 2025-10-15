#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/prctl.h>
#include <signal.h>

int main(void){	
	char name[16];

	prctl(PR_GET_NAME, (unsigned long *)name);
	printf("Process Name : %s\n", name);
	
	char *newname = "MyProcess";

	prctl(PR_SET_NAME, (unsigned long *)newname);

	memset(name, 0, 16);
	prctl(PR_GET_NAME, (unsigned long *)name);
	printf("Changed Process Name : %s\n", name);

	prctl(PR_SET_PDEATHSIG, SIGTERM);

	int sig;

	prctl(PR_GET_PDEATHSIG, &sig);
	printf("PR Death signal set to : %d : %s\n", sig, strsignal(sig));

	prctl(PR_SET_DUMPABLE, 0);
	printf("Core dump desabled for this process\n");

	int dump = prctl(PR_GET_DUMPABLE);
	printf("Dumpable Status : %d\n", dump);

	printf("PID : %d\n", getpid());


	return 0;
}
