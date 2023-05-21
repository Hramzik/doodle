

//--------------------------------------------------


#include "../hpp/func_testing.hpp"


//--------------------------------------------------


#include "../../lib/logs.hpp"


//--------------------------------------------------


Return_code hash_table_read_file (Hash_Table* table, const char* file_name) {

    if (!table)     { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!file_name) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    FILE* file = fopen (file_name, "rb");


    hash_table_read_file (table, file);


    fclose (file);


    return SUCCESS;
}


Return_code hash_table_read_file (Hash_Table* table, FILE* file) {

    if (!table) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!file) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    char* buffer = (char*) calloc (get_file_len (file), CHAR_SIZE);
    fread (buffer, CHAR_SIZE, get_file_len (file), file);
    char* buffer_ptr = buffer;


    char word [MAX_FUNC_TESTING_WORD_LEN] = "";

    while (read_word (&buffer_ptr, word) != SPECIAL_CASE) {

        hash_table_push (table, word);
    }


    free (buffer);


    return SUCCESS;
}


//--------------------------------------------------
#define my_src (*src_ptr)

Return_code read_word (char** src_ptr, char* dst) {

    if (!src_ptr) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!my_src)  { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!dst)     { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    while (is_space (*my_src)) { my_src += 1; }


    if (*my_src == '\0') return SPECIAL_CASE;


    while (is_word_part (*my_src)) {

        *dst = *my_src;

        dst    += 1;
        my_src += 1;
    }


    *dst = '\0';


    return SUCCESS;
}

#undef my_src
//--------------------------------------------------


bool is_space (char value) {

    if (value == ' ' || value == '\n' || value == '\t' || value == '\r') return true;


    return false;
}


bool is_word_part (char value) {

    if (is_space (value)) return false;
    if (value == '\0')    return false;


    return true;
}


Return_code hash_table_write_chain_sizes (Hash_Table* table, const char* file_name) {

    if (!table)     { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!file_name) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    FILE* file = fopen (file_name, "w");


    return hash_table_write_chain_sizes (table, file);
}


Return_code hash_table_write_chain_sizes (Hash_Table* table, FILE* file) {

    if (!table) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!file) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (int i = 0; i < table->size; i++) {

        fprintf (file, "%-5d %zd%s", i, hash_node_get_chain_size (table->buffer [i]), OUTPUT_SEPARATOR);
    }


    return SUCCESS;
}


size_t get_file_len (FILE* file) {

    if (!file) { LOG_ERROR (BAD_ARGS); return 0; }


    struct stat temp;
    fstat (fileno (file), &temp);


    return temp.st_size;
}


//--------------------------------------------------
#define HF_(n) HF_##n
#define OUTPUT_NAME(n) DEFAULT_DST_FILE_NAME #n ".txt"

#define test(n) {\
\
    Hash_Table* table = hash_table_ctor (TESTING_HASH_TABLE_SIZE, HF_(n));\
\
    hash_table_read_file (table);\
\
    hash_table_write_chain_sizes (table, OUTPUT_NAME (n));\
\
    hash_table_dtor (table);\
}\

Return_code test_7_hash_functions (void) {

    test (1);
    test (2);
    test (3);
    test (4);
    test (5);
    test (6);
    test (7);


    return SUCCESS;
}

