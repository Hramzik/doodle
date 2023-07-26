#ifndef LINKED_LIST_HPP_INCLUDED
#define LINKED_LIST_HPP_INCLUDED
//--------------------------------------------------


#include "includes.hpp"
#include "enums.hpp"
#include "structs.hpp"


//--------------------------------------------------


//List* create_list (             List_element_type element_type);
Node* create_node (void* value, List_element_type element_type);

Return_code list_ctor      (List* list, List_element_type element_type);
Return_code list_dtor      (List* list);
Return_code node_dtor      (Node* node);
Return_code list_push_back (List* list, void* value);
Return_code list_push_back (List* list, Player   player);
Return_code list_push_back (List* list, Platform platform);
Return_code list_insert    (List* list, Node* anker, void* value);
Return_code list_delete    (List* list, Node* node);

Return_code copy_player       (Player*   src, Player*   dst);
Return_code copy_platform     (Platform* src, Platform* dst);
Return_code copy_list_element (void*     src, void*     dst, List_element_type element_type);


Player*   node_get_player   (Node  node);
Platform* node_get_platform (Node  node);
Player*   node_get_player   (Node* node);
Platform* node_get_platform (Node* node);

Player*   list_get_player   (List list, size_t index);
Platform* list_get_platform (List list, size_t index);
void*     list_get_void_ptr (List list, size_t index);

size_t get_list_element_size (List_element_type element_type);


//--------------------------------------------------
#endif