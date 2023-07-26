#ifndef LINKED_LIST_HPP_INCLUDED
#define LINKED_LIST_HPP_INCLUDED
//--------------------------------------------------


#include "includes.hpp"
#include "enums.hpp"
#include "structs.hpp"


//--------------------------------------------------


List* create_list (List_element_type element_type);
Node* create_node (List_element_type element_type, void* value);

Return_code list_ctor      (List_element_type element_type);
Return_code list_dtor      (List* list);
Return_code node_dtor      (Node* node);
Return_code list_push_back (List* list, void* value);
Return_code list_insert    (List* list, Node* anker, void* value);
Return_code list_delete    (List* list, Node* node);

Return_code copy_player   (Player*   src, Player*   dst);
Return_code copy_platform (Platform* src, Platform* dst);

Player*   list_get_player   (List list, size_t index);
Platform* list_get_platform (List list, size_t index);
void*     list_get_void_ptr (List list, size_t index);


//--------------------------------------------------
#endif