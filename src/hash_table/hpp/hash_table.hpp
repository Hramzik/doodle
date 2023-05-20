#ifndef HASH_TABLE_HPP_INCLUDED
#define HASH_TABLE_HPP_INCLUDED
//--------------------------------------------------


#include "enums.hpp"
#include "../../lib/types/Return_code.hpp"


//--------------------------------------------------


#include "enums.hpp"


//--------------------------------------------------


typedef char* Element;

typedef struct Hash_Node {

    Element key;

    Hash_Node* next;

} Hash_Node; const size_t HASH_NODE_SIZE = sizeof (Hash_Node);



typedef struct Hash_Table {

    Hash_Node* buffer;

    size_t size;

} Hash_Table; const size_t HASH_TABLE_SIZE = sizeof (Hash_Table);


//--------------------------------------------------


Hash_Table  hash_table_ctor (void);
Return_code hash_table_dtor (Hash_Table* table);
Return_code hash_table_push (Hash_Table* table);


//--------------------------------------------------
#endif