#ifndef ARRAY_HPP_INCLUDED
#define ARRAY_HPP_INCLUDED
//--------------------------------------------------


#include "enums.hpp"
#include "structs.hpp"
#include "includes.hpp"


//--------------------------------------------------


Return_code array_ctor (Array* array, Array_element_type element_type);
Return_code array_dtor (Array* array);

Return_code array_push (Array* array, SDL_Texture* texture);
Return_code array_push (Array* array, Hitbox_Rect rect);
Return_code array_push (Array* array, Player_Skin skin);
Return_code array_push (Array* array, Platform_Skin skin);
Return_code array_push (Array* array, Platform_type type);

Return_code array_resize_up          (Array* array);

//--------------------------------------------------

SDL_Texture*  array_get_texture       (Array array, size_t index);
Hitbox_Rect   array_get_hitbox_rect   (Array array, size_t index);
Platform_type array_get_platform_type (Array array, size_t index);
Player_Skin   array_get_player_skin   (Array array, size_t index);
Platform_Skin array_get_platform_skin (Array array, size_t index);
void*         array_get_void_ptr      (Array array, size_t index);

//--------------------------------------------------

size_t get_array_element_size (Array_element_type element_type);

//--------------------------------------------------

Return_code array_destroy_textures (Array* array);

//--------------------------------------------------
#endif