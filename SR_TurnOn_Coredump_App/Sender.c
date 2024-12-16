#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    pid_t receiver_pid;
    int input;
    union sigval value;

    printf("Enter the PID of the receiver process: ");
    scanf("%d", &receiver_pid);

    printf("Enter 0 to terminate, 1 to abort: ");
    scanf("%d", &input);

    if (input == 0 || input == 1) 
    {
        value.sival_int = input;
        if (sigqueue(receiver_pid, SIGRTMIN, value) == -1) 
        {
            perror("Failed to send signal");
            exit(EXIT_FAILURE);
        }
        printf("Signal sent with data %d to process %d\n", input, receiver_pid);
        
    } else
    {
        printf("Invalid input! Please enter 0 or 1.\n");
    }

    return 0;
}
