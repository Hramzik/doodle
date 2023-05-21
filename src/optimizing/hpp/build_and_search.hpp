#ifndef BUILD_AND_SEARCH_HPP_INCLUDED
#define BUILD_AND_SEARCH_HPP_INCLUDED
//--------------------------------------------------


#include "stdio.h"
#include "stdlib.h"
#include <sys\stat.h>


//--------------------------------------------------


#include "../../lib/types/Return_code.hpp"


//--------------------------------------------------


#include "../../hash_table/hpp/hash_table.hpp"
#include "../../func_testing/hpp/func_testing.hpp"
#include "../../timer/hpp/timer.hpp"


//--------------------------------------------------


#include "constants.hpp"


//--------------------------------------------------


Return_code build_table_and_search_words (const char* src_file_name    = DEFAULT_SRC_FILE_NAME,
                                          const char* search_file_name = DEFAULT_SEARCH_FILE_NAME);

char* get_file_buffer (const char* file_name);


//--------------------------------------------------
#endif