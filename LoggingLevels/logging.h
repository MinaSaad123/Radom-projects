#ifndef    LOGGING_H
#define    LOGGING_H

//============================================================================================//
//                                       User-define
//============================================================================================//
typedef enum
{
    LOG_error = 1,
    LOG_warning,
    LOG_info,
    LOG_debug 

}logLevel_t;
//============================================================================================//
//                                       APIs prototype
//============================================================================================//
void LOG_ERROR(char* message);
void LOG_WARNING(char* message);
void LOG_INFO(char* message);
void LOG_DEBUG(char* message);
void LOG_loop();
void changeLevel(logLevel_t level);
#endif