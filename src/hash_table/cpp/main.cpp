

//--------------------------------------------------

#include "../hpp/hash_table.hpp"

//--------------------------------------------------


int main (void) {

    Hash_Table* table = hash_table_ctor (10, HF_7);

    for (size_t i = 0; i < 500; i++) {

        char* string = (char*) calloc (100, CHAR_SIZE);
        sprintf (string, "%zd", i);

        hash_table_push (table, string);
    }


    hash_table_print (table);


    hash_table_dtor (table);


    printf ("goodbye!\n");


    return 0;
}

