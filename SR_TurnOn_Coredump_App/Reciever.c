#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_signal(int sig, siginfo_t *info, void *context)
{
    int data = info->si_value.sival_int; /* Retrieve the data sent with the signal*/

    if (data == 0) 
    {
        printf("Received data 0. Terminating gracefully...\n");
        exit(0);
        
    } else if (data == 1)
    {
        printf("Received data 1. Aborting with core dump...\n");
        abort();
        
    } else
    {
        printf("Received invalid data: %d. Ignoring...\n", data);
    }
}

int main()
{
    struct sigaction sa;

    printf("Receiver process started. PID: %d\n", getpid());
    printf("Waiting for real-time signals...\n");

    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO; /* Use SA_SIGINFO to access the signal data*/
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGRTMIN, &sa, NULL) == -1)
    {
        perror("Failed to set signal handler");
        exit(EXIT_FAILURE);
    }

    while (1);

    return 0;
}
