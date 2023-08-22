

//--------------------------------------------------

#include "../hpp/array.hpp"

//--------------------------------------------------



size_t get_array_element_size (Array_element_type element_type) {

    switch (element_type) {

        case AET_SDL_TEXTURE: return sizeof (SDL_Texture*);

        default: LOG_ERROR (CRITICAL); return 0;
    }
}


SDL_Texture* array_get_texture (Array array, size_t index) {


    return (SDL_Texture*) array_get_void_ptr (array, index);
}


void* array_get_void_ptr (Array array, size_t index) {

    if (index >= array.size) { LOG_ERROR (BAD_ARGS); return nullptr; }


    return *(char**)((char*) array.buffer + index * get_array_element_size (array.element_type));
}


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


    void* dst = (char*) array->buffer + array->size * get_array_element_size (array->element_type);
    memcpy (dst, value, value_size);


    array->size += 1;


    return SUCCESS;
}


Return_code array_resize_up (Array* array) {

    if (!array) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    size_t new_capacity = 2 * my_max (array->capacity, 1);
    size_t new_buffer_size = get_array_element_size (array->element_type) * new_capacity;


    array->buffer = realloc (array->buffer, new_buffer_size);


    array->capacity = new_capacity;


    return SUCCESS;
}


Return_code array_destroy_textures (Array* array) {

    if (!array) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (array->element_type != AET_SDL_TEXTURE) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < array->size; i++) {

        SDL_DestroyTexture (array_get_texture (*array, i));
    }


    return SUCCESS;
}

