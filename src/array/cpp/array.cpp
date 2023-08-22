

//--------------------------------------------------

#include "../hpp/array.hpp"

//--------------------------------------------------



size_t get_array_element_size (Array_element_type element_type) {

    switch (element_type) {

        case AET_SDL_TEXTURE: return sizeof (SDL_Texture*);

        default: LOG_ERROR (CRITICAL); return 0;
    }
}

/*
Return_code copy_array_element (void* src, void* dst, Array_element_type element_type) {

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
*/

SDL_Texture* array_get_texture (Array array, size_t index) {


    return (SDL_Texture*) array_get_void_ptr (array, index);
}


void* array_get_void_ptr (Array array, size_t index) {

    return *(char**)((char*) array.buffer + index * get_array_element_size (array.element_type));
}

/*
Array* create_array (Array_element_type element_type) {

    Array* array = (Array*) calloc (1, ARRAY_SIZE);


    array->first = nullptr;
    array->last  = nullptr;

    array->element_type = element_type;
    array->len          = 0;


    return array;
}*/

Return_code array_ctor (Array* array, Array_element_type element_type) {

    if (!array) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    array->buffer = nullptr;
    array->element_type = element_type;

    array->capacity = 0;
    array->size     = 0;


    return SUCCESS;
}


Return_code array_dtor (Array* array) {

    if (!array) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    free (array->buffer);


    return SUCCESS;
}


Return_code array_push (Array* array, SDL_Texture* texture) {

    if (!array)                                 CODE_BAD_ARGS;
    if (array->element_type != AET_SDL_TEXTURE) CODE_BAD_ARGS;


    array_push (array, &texture, sizeof (SDL_Texture*));


    return SUCCESS;
}


Return_code array_push (Array* array, void* value, size_t value_size) {

    if (!array) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (array->size == array->capacity) array_resize_up (array);

printf ("debug: pushing %p\n", * (char**) value);
    void* dst = (char*) array->buffer + array->size * get_array_element_size (array->element_type);
    memcpy (dst, value, value_size);


    array->size += 1;


    return SUCCESS;
}


Return_code array_resize_up (Array* array) {

    if (!array) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    size_t capacity_round_up = my_max (array->capacity, 1);
    size_t new_capacity = 2 * get_array_element_size (array->element_type) * capacity_round_up;


    array->buffer = realloc (array->buffer, new_capacity);


    array->capacity = new_capacity;


    return SUCCESS;
}

