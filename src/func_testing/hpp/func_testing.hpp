#ifndef FUNC_TESTING_HPP_INCLUDED
#define FUNC_TESTING_HPP_INCLUDED
//--------------------------------------------------


#include "stdio.h"
#include "stdlib.h"
#include <sys\stat.h>


//--------------------------------------------------


#include "../../lib/types/Return_code.hpp"


//--------------------------------------------------


#include "../../hash_table/hpp/hash_table.hpp"


//--------------------------------------------------


#include "constants.hpp"


//--------------------------------------------------


Return_code hash_table_read_file (Hash_Table* table, const char* filename = DEFAULT_SRC_FILE_NAME);
Return_code hash_table_read_file (Hash_Table* table, FILE* file);
Return_code read_word            (char** src_ptr, char* dst);
bool        is_space             (char value);
bool        is_word_part         (char value);

Return_code hash_table_write_chain_sizes (Hash_Table* table, const char* filename = DEFAULT_DST_FILE_NAME);
Return_code hash_table_write_chain_sizes (Hash_Table* table, FILE* file);

size_t get_file_len (FILE* file);

Return_code test_7_hash_functions (void);


//--------------------------------------------------
#endif