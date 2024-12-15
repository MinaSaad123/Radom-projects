#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() 
{
    pid_t receiver_pid;
    int input;

    printf("Enter the PID of the receiver process: ");
    scanf("%d", &receiver_pid);

    printf("Enter 0 to terminate, 1 to abort: ");
    scanf("%d", &input);

    if (input == 0) 
    {
        
        if (kill(receiver_pid, SIGTERM) == -1) /* Send SIGTERM to the receiver*/
        {
            perror("Failed to send SIGTERM");
            exit(1);
        }
        
        printf("SIGTERM signal sent to process %d\n", receiver_pid);
    
    } else if (input == 1) 
    {
        // Send SIGABRT to the receiver
        if (kill(receiver_pid, SIGABRT) == -1) 
        {
            perror("Failed to send SIGABRT");
            exit(1);
        }
        
        printf("SIGABRT signal sent to process %d\n", receiver_pid);
    
    } else 
    {
        // Handle invalid input
        printf("Invalid input! Please enter 0 or 1.\n");
    }

    return 0;
}
