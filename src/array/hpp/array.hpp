#ifndef ARRAY_HPP_INCLUDED
#define ARRAY_HPP_INCLUDED
//--------------------------------------------------


#include "includes.hpp"
#include "enums.hpp"
#include "structs.hpp"


//--------------------------------------------------


Return_code array_ctor (Array* array, Array_element_type element_type);
Return_code array_dtor (Array* array);

Return_code array_push (Array* array, SDL_Texture* texture);
Return_code array_push (Array* array, void* value, size_t value_size);
Return_code array_double_capacity (Array* array);

//--------------------------------------------------

SDL_Texture* array_get_texture  (Array array, size_t index);
void*        array_get_void_ptr (Array array, size_t index);

//--------------------------------------------------

size_t get_array_element_size (Array_element_type element_type);

//--------------------------------------------------
#endif