#ifndef HASH_TABLE_HPP_INCLUDED
#define HASH_TABLE_HPP_INCLUDED
//--------------------------------------------------


#include "stdio.h"
#include "stdlib.h"
#include "string.h"


//--------------------------------------------------


#include "../../lib/types/Return_code.hpp"


//--------------------------------------------------


#include "enums.hpp"
#include "constants.hpp"
#include "abbreviations.hpp"


//--------------------------------------------------


typedef struct Hash_Node {

    char*      value;
    Hash_Node* next;

} Hash_Node; const size_t HASH_NODE_SIZE = sizeof (Hash_Node);



typedef struct Hash_Table {

    Hash_Node** buffer;
    int         size;   // cause hash result are int

    Hash_function hash_function;

} Hash_Table; const size_t HASH_TABLE_SIZE = sizeof (Hash_Table);


//--------------------------------------------------


Hash_Table* hash_table_ctor (int size, Hash_function hash_function = HF_CRC32);
Return_code hash_table_dtor (Hash_Table* table);
Return_code hash_node_dtor  (Hash_Node*  node);

Return_code hash_table_push  (Hash_Table* table,    const char* value);
Return_code hash_node_push   (Hash_Node*  node,     const char* value);
Return_code create_hash_node (Hash_Node** node_ptr, const char* value);

bool hash_table_search (Hash_Table* table, const char* value);
bool hash_node_search  (Hash_Node* node,   const char* value);

int hash_table_get_hash (Hash_Table* table, const char* value);

Return_code hash_table_print (Hash_Table* table);
Return_code hash_nodes_print (Hash_Node* node);

size_t hash_node_get_chain_size (Hash_Node* node);

//--------------------------------------------------

int hf_constant_one  (const char* value);
int hf_first_char    (const char* value);
int hf_strlen        (const char* value);
int hf_sum_char      (const char* value);
int hf_rorxor        (const char* value);
int hf_rolxor        (const char* value);
int hf_crc32         (const char* value);


//--------------------------------------------------
#endif