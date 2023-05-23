

//--------------------------------------------------


#include "../hpp/build_and_search.hpp"


//--------------------------------------------------


#include "../../lib/logs.hpp"


//--------------------------------------------------

Return_code build_table_and_search_words (const char* src_file_name, const char* search_file_name) {

    if (!src_file_name)    { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!search_file_name) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Timer* timer = timer_ctor ();


    Hash_Table* table = hash_table_ctor (SEARCH_HASH_TABLE_SIZE, HF_CRC32_OPT_2);
    hash_table_read_file (table, src_file_name);


    char* buffer                     = get_file_buffer (search_file_name);
    char* buffer_ptr                 = buffer;
    char  word [MAX_SEARCH_WORD_LEN] = "";


    size_t words_searched = 0;
    size_t words_found    = 0;

    while (read_word (&buffer_ptr, word) != SPECIAL_CASE) {

        for (size_t i = 0; i < NUMBER_OF_SEARCHES - 1; i++) hash_table_search (table, word);

        if (hash_table_search (table, word)) words_found += 1;

        words_searched += 1;
    }


    printf ("words searched %zd\n", words_searched);
    printf ("words found %zd (%zd%%)\n", words_found, 100 * words_found / words_searched);
    printf ("total time %zd ms\n\n", timer_get_total_delay_ms (timer));


    free       (buffer);
    timer_dtor (timer);


    return SUCCESS;
}


char* get_file_buffer (const char* file_name) {

    if (!file_name) { LOG_ERROR (BAD_ARGS); return nullptr; }


    FILE* file = fopen (file_name, "rb");


    char* buffer = (char*) calloc (CHAR_SIZE, get_file_len (file));
    fread (buffer, CHAR_SIZE, get_file_len (file), file);


    fclose (file);


    return buffer;
}

