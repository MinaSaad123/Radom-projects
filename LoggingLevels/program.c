//--------------------------<Include>
#define _POSIX_C_SOURCE  199309L  
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include "logging.h"

void realTimeSig_Handler (int sigNum, siginfo_t* info, void *context) /*real-time handler*/
{
    changeLevel(info->si_value.sival_int);
}

void main(int argc, char **argv)
{
    struct sigaction sa;

    LOG_INFO("[INFO] In the begining of main\n");

    sa.sa_sigaction = realTimeSig_Handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask); /*To ensure the struct is empty*/

    //passing the struct to sigaction
    if ( sigaction(SIGRTMIN, &sa, NULL) == -1 )
    {
        perror("[ERROR] sigaction");
        exit(1);
    }

    /* Try to open a file*/
    if (argc > 2)
    {
        if ( open(argv[1], O_CREAT | O_RDWR | O_WRONLY, 0644) == -1 )
        {
            LOG_WARNING("[WARNING] I will get down open() system call to test LOG_ERROR\n");

            LOG_ERROR("[ERROR] Fail for open system call to test LOG_ERROR\n");
            exit(1);
        }
    }

    LOG_DEBUG("[DEBUG] just to test no debug need for now\n");

    LOG_INFO("[INFO] at the end of main\n");

    LOG_loop(); //looping
}