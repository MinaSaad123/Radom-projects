#define _POSIX_C_SOURCE 200809L  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <unistd.h>


void handle_sigchld(int signum, siginfo_t *info, void *context) 
{
    if (info->si_code == CLD_EXITED)
    {
        printf("Child PID %d exited normally with status %d\n", info->si_pid, info->si_status);

    } else if (info->si_code == CLD_KILLED || info->si_code == CLD_DUMPED)
    {
        printf("Child PID %d was terminated by signal %d\n", info->si_pid, info->si_status);
    }
}

int main() 
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;  
    sa.sa_sigaction = handle_sigchld;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGCHLD, &sa, NULL) == -1) 
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; i++) 
    {
        pid_t pid = fork();

        if (pid == -1) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) 
        {  
            sleep(2 + i); 
            exit(1);
        }
    }

    for (int i = 0; i < 10; i++) 
    {
        printf("Parent working...\n");
        sleep(1);
    }

    return 0;  
}