#ifndef LINKED_LIST_STRUCTS_HPP_INCLUDED
#define LINKED_LIST_STRUCTS_HPP_INCLUDED
//--------------------------------------------------


#include "enums.hpp"


//--------------------------------------------------


typedef struct Node {

    void* value;

    Node* prev;
    Node* next;

} Node; const size_t NODE_SIZE = sizeof (Node);



typedef struct List {

    Node* first;
    Node* last;

    List_element_type element_type;
    size_t            len;

} List; const size_t LIST_SIZE = sizeof (List);


//--------------------------------------------------
#endif