#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void){
	char *jail_dir = "/tmp/jail_dir";

	mkdir(jail_dir, 0755);
	printf("Created directory %s\n", jail_dir);

	FILE *fp = fopen("/tmp/jail_dir/testfile.txt", "w");
    	if(fp){
        	fprintf(fp, "Hello from inside the jail!\n");
        	fclose(fp);
    	}

	chroot(jail_dir);

	chdir("/");

	printf("Entered chroot /tmp/jail_dir successfully\n");
	printf("current cwd : %s\n", getcwd(NULL, 0));

	printf("Listing files inside /tmp/jail_dir\n");
	system("ls -l /");

	printf("Cleaning up /tmp/jail_dir\n");
	system("rm -rf /tmp/jail_dir");
	printf("cleanup completed\n");

	return 0;
}
