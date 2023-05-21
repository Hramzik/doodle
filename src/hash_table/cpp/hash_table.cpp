

//--------------------------------------------------


#include "../hpp/hash_table.hpp"


//--------------------------------------------------


#include "../../lib/logs.cpp"


//--------------------------------------------------


#include "hash_functions.cpp"


//--------------------------------------------------


Hash_Table* hash_table_ctor (int size, Hash_function hash_function) {

    Hash_Table* table = (Hash_Table*) calloc (1, HASH_TABLE_SIZE);


    table->buffer = (Hash_Node**) calloc (size, sizeof (Hash_Node*));

    for (int i = 0; i < size; i++) {

        table->buffer [i] = nullptr;
    }


    table->size = size;


    table->hash_function = hash_function;


    return table;
}


Return_code hash_table_dtor (Hash_Table* table) {

    if (!table) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (int i = 0; i < table->size; i++) {

        hash_node_dtor (table->buffer [i]);
    }


    free (table);


    return SUCCESS;
}


Return_code hash_node_dtor (Hash_Node* node) {

    if (!node) return SUCCESS;


    hash_node_dtor (node->next);


    free (node->value);
    free (node);


    return SUCCESS;
}


Return_code hash_table_push (Hash_Table* table, const char* value) {

    if (!table) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    unsigned int index = (unsigned int) hash_table_get_hash (table, value) % table->size;


    if (!table->buffer [index]) create_hash_node (&table->buffer [index], value);
    else                        hash_node_push   ( table->buffer [index], value);


    return SUCCESS;
}


//--------------------------------------------------
#define my_node (*node_ptr)

Return_code create_hash_node (Hash_Node** node_ptr, const char* value) {

    if (!node_ptr) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (*node_ptr) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    my_node = (Hash_Node*) calloc (HASH_NODE_SIZE, 1);

    my_node->next  = nullptr;
    my_node->value = strdup (value);


    return SUCCESS;
}

#undef my_node
//--------------------------------------------------

Return_code hash_node_push (Hash_Node* node, const char* value) {

    if (!node) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Hash_Node* last_node = nullptr;

    while (node) {

        if (!strcmp (node->value, value)) return SUCCESS; // no duplicates

        last_node = node;
        node = node->next;
    }


    create_hash_node (&last_node->next, value);


    return SUCCESS;
}


int hash_table_get_hash (Hash_Table* table, const char* value) {

    if (!table) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (table->hash_function) {

        case HF_CONSTANT_ONE: return hf_constant_one (value);
        case HF_FIRST_CHAR:   return hf_first_char   (value);
        case HF_STRLEN:       return hf_strlen       (value);
        case HF_SUM_CHAR:     return hf_sum_char     (value);
        case HF_RORXOR:       return hf_rorxor       (value);
        case HF_ROLXOR:       return hf_rolxor       (value);
        case HF_CRC32:        return hf_crc32        (value);

        default: LOG_ERROR (CRITICAL); return 0;
    }


    return 0; // never happens
}


Return_code hash_table_print (Hash_Table* table) {

    if (!table) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (int i = 0; i < table->size; i++) {

        printf ("hash %d: ", i);
        hash_nodes_print (table->buffer [i]);
        printf ("\n");
    }


    return SUCCESS;
}


Return_code hash_nodes_print (Hash_Node* node) {

    while (node) {

        printf ("%s ", node->value);
        node = node->next;
    }


    return SUCCESS;
}


size_t hash_node_get_chain_size (Hash_Node* node) {

    size_t ans = 0;

    while (node) {

        node = node->next;

        ans += 1;
    }


    return ans;
}

bool hash_table_search (Hash_Table* table, const char* value) {

    if (!table) { LOG_ERROR (BAD_ARGS); return false; }
    if (!value) { LOG_ERROR (BAD_ARGS); return false; }


    for (int i = 0; i < table->size; i++) {

        if (hash_node_search (table->buffer [i], value)) return true;
    }


    return false;
}


bool hash_node_search (Hash_Node* node, const char* value) {

    if (!value) { LOG_ERROR (BAD_ARGS); return false; }


    if (!node) return false;


    if (!strcmp (node->value, value)) return true;


    return hash_node_search (node->next, value);
}


