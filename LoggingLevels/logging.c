//-----------------------------------------<include>
#include "logging.h"
#include <stdio.h>
//============================================================================================//
//                                       Global variables
//============================================================================================//
logLevel_t logs[30];
char* Log_ADRS[30];
int count;
//=============================================================================================

void LOG_loop()
{
    while(1);
}

void LOG_ERROR(char* message)
{
    Log_ADRS[count] = message;
    logs[count] = LOG_error;
    ++count;
}

void LOG_WARNING(char* message)
{
    Log_ADRS[count] = message;
    logs[count] = LOG_warning;
    ++count;
}

void LOG_INFO(char* message)
{
    Log_ADRS[count] = message;
    logs[count] = LOG_info;
    ++count;
}

void LOG_DEBUG(char* message)
{
    Log_ADRS[count] = message;
    logs[count] = LOG_debug;
    ++count;
}

void changeLevel(logLevel_t level)
{
    int c;

    if ( level == LOG_debug )
    {    
        for (c = 0;c < count;++c)
        {
            printf("%s", Log_ADRS[c]);
        }   

    } else if ( level == LOG_warning )
    {
        for (c = 0;c < count;++c)
        {
            if ( logs[c] != LOG_debug )
            {
                printf("%s", Log_ADRS[c]);
            }
        }   

    } else if ( level == LOG_info )
    {
        for (c = 0;c < count;++c)
        {
            if ( logs[c] == LOG_info || logs[c] == LOG_error  )
            {
                printf("%s", Log_ADRS[c]);
            }
        }   

    } else if ( level == LOG_error )
    {
        for (c = 0;c < count;++c)
        {
            if ( logs[c] == LOG_error)
            {
                printf("%s", Log_ADRS[c]);
            }
        }   

    }
     else
    {
        printf("the sended value from the another process is invalid\n");
    }

}

