#ifndef LOGS_HPP_INCLUDED
#define LOGS_HPP_INCLUDED
//--------------------------------------------------


#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "types/Return_code.hpp"


//--------------------------------------------------


#define log_file_name "work/logs.txt"
#define LOG_MESSAGE(message) _log_message (message, __FILE__, __PRETTY_FUNCTION__, __LINE__)


//--------------------------------------------------


static const size_t time_str_len  = 40;
static const bool   save_old_logs = false;


//--------------------------------------------------


void       _log_error              (Return_code, const char*, const char*, int);
void       _log_message            (const char* message, const char* file, const char* func, const int line);
void        log_start              (void);
void        log_end                (void);
void        print_log_time         (void);
char*       tm_to_str              (struct tm* time_structure);


//--------------------------------------------------


#define CODE_CRITICAL   { LOG_ERROR (CRITICAL);   return CRITICAL;   }
#define CODE_FILE_ERR   { LOG_ERROR (FILE_ERR);   return FILE_ERR;   }
#define CODE_MEMORY_ERR { LOG_ERROR (MEMORY_ERR); return MEMORY_ERR; }
#define CODE_BAD_ARGS   { LOG_ERROR (BAD_ARGS);   return BAD_ARGS;   }
#define CODE_LIB_ERR    { LOG_ERROR (LIB_ERR);    return LIB_ERR;    }


//--------------------------------------------------
#endif