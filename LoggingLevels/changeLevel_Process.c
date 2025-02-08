//--------------------------<Include>
#define _POSIX_C_SOURCE  199309L  
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void main(int argc, char **argv)
{
    union sigval value;
    value.sival_int = ( strcmp(argv[1], "error") == 0 ) ? 1 
                    : ( strcmp(argv[1], "warning") == 0 ) ? 2
                    : ( strcmp(argv[1], "info") == 0 ) ? 3
                    : ( strcmp(argv[1], "debug") == 0 ) ? 4
                    : 0; 

    if ( value.sival_int != 0)
    {
        if (sigqueue(atoi(argv[2]), SIGRTMIN, value) == -1) 
        {
         perror("sigqueue");
        }
    }
}