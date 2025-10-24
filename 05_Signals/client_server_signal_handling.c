#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void server_handler(int sig)
{
    if (sig == SIGUSR1)
        printf("Server: Received SIGUSR1 from client\n");
    if (sig == SIGUSR2)
        printf("Server: Received SIGUSR2 from client\n");
}

int main()
{
    pid_t pid;

    pid = fork(); 

    if (pid == 0)
    {
        sleep(2); 

        pid_t server_pid = getppid(); 
        printf("Client: Sending SIGUSR1 to server (PID=%d)\n", server_pid);
        kill(server_pid, SIGUSR1);

        sleep(2);
        printf("Client: Sending SIGUSR2 to server (PID=%d)\n", server_pid);
        kill(server_pid, SIGUSR2);

        sleep(1);
        printf("Client: Exiting...\n");
        exit(0);
    }
    else
    {
        struct sigaction sa;
        sa.sa_handler = server_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;

        if (sigaction(SIGUSR1, &sa, NULL) == -1)
        {
            perror("sigaction(SIGUSR1)");
            exit(EXIT_FAILURE);
        }
        if (sigaction(SIGUSR2, &sa, NULL) == -1)
        {
            perror("sigaction(SIGUSR2)");
            exit(EXIT_FAILURE);
        }

        printf("Server (PID=%d) waiting for client signals...\n", getpid());

        while (1)
        {
            pause();
        }
    }

    return 0;
}

