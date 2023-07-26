

//--------------------------------------------------

#include "../hpp/list.hpp"

//--------------------------------------------------



size_t get_list_element_size (List_element_type element_type) {

    switch (element_type) {

        case LET_PLAYER:   return PLAYER_SIZE;
        case LET_PLATFORM: return PLATFORM_SIZE;

        default: LOG_ERROR (CRITICAL); return 0;
    }
}


Return_code copy_list_element (void* src, void* dst, List_element_type element_type) {

    if (!src) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!dst) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Player*   src_player   = (Player*)   src;
    Player*   dst_player   = (Player*)   dst;
    Platform* src_platform = (Platform*) src;
    Platform* dst_platform = (Platform*) dst;


    switch (element_type) {

        case LET_PLAYER:   return copy_player   (src_player,   dst_player);
        case LET_PLATFORM: return copy_platform (src_platform, dst_platform);

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



Player*   node_get_player   (Node node) { return (Player*)   node.value; }
Platform* node_get_platform (Node node) { return (Platform*) node.value; }


Player* node_get_player (Node* node) {

    if (!node) { LOG_ERROR (BAD_ARGS); return nullptr; }


    return node_get_player (*node);
}


Platform* node_get_platform (Node* node) {

    if (!node) { LOG_ERROR (BAD_ARGS); return nullptr; }


    return node_get_platform (*node);
}


Player* list_get_player (List list, size_t index) {


    return (Player*) list_get_void_ptr (list, index);
}


Platform* list_get_platform (List list, size_t index) {


    return (Platform*) list_get_void_ptr (list, index);
}


void* list_get_void_ptr (List list, size_t index) {

    Node* cur_node = list.first;

    for (size_t i = 0; i < index; i++) {

        if (!cur_node) { LOG_ERROR (BAD_ARGS); return nullptr; }

        cur_node = cur_node->next;
    }


    return cur_node->value;
}

/*
List* create_list (List_element_type element_type) {

    List* list = (List*) calloc (1, LIST_SIZE);


    list->first = nullptr;
    list->last  = nullptr;

    list->element_type = element_type;
    list->len          = 0;


    return list;
}*/


Node* create_node (void* value, List_element_type element_type) {

    Node* node = (Node*) calloc (1, NODE_SIZE);


    node->next = nullptr;
    node->prev = nullptr;

    node->value = calloc (1, get_list_element_size (element_type));
    copy_list_element (value, node->value, element_type);


    return node;
}


Return_code list_ctor (List* list, List_element_type element_type) {

    if (!list) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


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


    //free (list);


    return SUCCESS;
}


Return_code node_dtor (Node* node) {

    if (!node) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    free (node->value);
    free (node);


    return SUCCESS;
}


Return_code list_push_back (List* list, Player player) {

    if (!list)                            CODE_BAD_ARGS;
    if (list->element_type != LET_PLAYER) CODE_BAD_ARGS;


    list_push_back (list, &player);


    return SUCCESS;
}


Return_code list_push_back (List* list, Platform platform) {

    if (!list)                              CODE_BAD_ARGS;
    if (list->element_type != LET_PLATFORM) CODE_BAD_ARGS;


    list_push_back (list, &platform);


    return SUCCESS;
}


Return_code list_push_back (List* list, void* value) {

    if (!list) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Node* node = create_node (value, list->element_type);
    list->len += 1;


    if (list->len == 1) { // ДО ЭТОГО БЫЛО 0!!!

        list->first = node;
        list->last  = node;
        return SUCCESS;
    }


    node->prev = list->last;

    if (list->last) list->last->next = node;


    list->last = node;


    return SUCCESS;
}


Return_code list_insert (List* list, Node* anker, void* value) {

    if (!anker) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Node* node = create_node (value, list->element_type);
    list->len += 1;


    node->prev = anker;
    node->next = anker->next;

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

