#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Handler for SIGTERM
void handle_sigterm(int sig) 
{
    printf("Received SIGTERM (signal %d). Terminating...\n", sig);
    exit(0);
}

// Handler for SIGABRT
void handle_sigabrt(int sig) 
{
    printf("Received SIGABRT (signal %d). Aborting with core dump...\n", sig);
    abort();
}

int main()
{
    printf("Receiver process started. PID: %d\n", getpid());
    printf("Waiting for signals...\n");

    // Register handlers for SIGTERM and SIGABRT
    if (signal(SIGTERM, handle_sigterm) == -1)
    {
        perror("Failed to set SIGTERM handler");
        exit(1);
    }
    if (signal(SIGABRT, handle_sigabrt) == -1)
    {
        perror("Failed to set SIGABRT handler");
        exit(1);
    }

    // Keep the process running to wait for signals
    while (1);

    return 0;
}
