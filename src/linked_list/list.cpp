

//--------------------------------------------------

#include "list.hpp"

//--------------------------------------------------



size_t get_list_element_size (List_element_type element_type) {

    switch (element_type) {

        case LET_PLAYER:   return PLAYER_SIZE;
        case LET_PLATFORM: return PLATFORM_SIZE;

        default: LOG_ERROR (CRITICAL)l return 0;
    }
}


Return_code copy_list_element (void* src, void* dst, List_element_type element_type) {

    if (!src) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!dst) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (element_type) {

        case LET_PLAYER:   return copy_player   (src, dst);
        case LET_PLATFORM: return copy_platform (src, dst);

        default: CODE_CRITICAL;
    }
}


Return_code copy_player (Player* src, Player* dst) {

    if (!src) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!dst) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    *dst = *src;


    return SUCCESS;
}


Return_code copy_platform (Platform* src, Platform* dst) {

    if (!src) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!dst) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    *dst = *src;


    return SUCCESS;
}


Player* list_get_player (List* list, size_t index) {

    if (!list) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return list_get_void_ptr (list, index);
}


Platform* list_get_platform (List* list, size_t index) {

    if (!list) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return list_get_void_ptr (list, index);
}


void* list_get_void_ptr (List* list, size_t index) {

    if (!list) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Node* cur_node = list->first;

    for (size_t i = 0; i < index; i++) {

        cur_node = cur_node->next;
    }


    return cur_node->value;
}


List* create_list (List_element_type element_type) {

    List* list = (List*) calloc (1, LIST_SIZE);


    list->first = nullptr;
    list->last  = nullptr;

    list->element_type = element_type;
    list->len          = 0;


    return list;
}


Node* create_node (List_element_type element_type, void* value) {

    Node* node = (Node*) calloc (1, NODE_SIZE);


    node->next = nullptr;
    node->prev = nullptr;

    node->value = calloc (1, get_list_element_size (element_type));
    copy_list_element (value, node->value, List_element_type);


    return node;
}


Return_code list_ctor (List_element_type element_type) {

    list->first = nullptr;
    list->last  = nullptr;

    list->element_type = element_type;
    list->len          = 0;


    return SUCCESS;
}


Return_code list_dtor (List* list) {

    if (!list) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Node* cur_node  = list->first;
    Node* next_node = nullptr;

    while (cur_node) {

        next_node = cur_node->next;
        node_dtor (cur_node);
        cur_node = next_node;
    }


    free (list)


    return SUCCESS;
}


Return_code node_dtor (Node* node) {

    if (!node) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    free (node->value);
    free (node);


    return SUCCESS;
}


Return_code list_push_back (List* list, void* value) {

    if (!list) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Node* node = create_node (value, list->element_type);
    list->len += 1;


    if (!list->len) {

        list->first = node;
        list->last  = node;
        return SUCCESS;
    }


    node->prev = list->last;
    list->last->next = node;

    list->last = node;


    return SUCCESS;
}


Return_code list_insert (List* list, Node* anker, void* value) {

    if (!anker) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Node* node = create_node (value, list->element_type);
    list->len += 1;


    node->prev = anker;
    node->next = prev->next;

    if (anker->next) anker->next->prev = node;

    anker->next = node;


    return SUCCESS;
}


Return_code list_delete (List* list, Node* node) {

    if (!list) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!node) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;


    node_dtor (node);
    list->len -= 1;


    return SUCCESS;
}

