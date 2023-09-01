

//--------------------------------------------------


#include "../hpp/game.hpp"


//--------------------------------------------------


Return_code game_load_media (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_load_background_textures (game);
    game_load_player_skins        (game);
    game_load_platform_skins   (game);


    return SUCCESS;
}


SDL_Texture* game_get_sdl_texture (Game* game, const char* path, bool transparent_flag, My_RGB clr) {

    if (!path) { LOG_ERROR (BAD_ARGS); return nullptr; }


    SDL_Surface* temp_surface = IMG_Load (path);

    if(!temp_surface) {

        LOG_MESSAGE ("Unable to load image!\n");
        return nullptr;
    }

    if (transparent_flag) {

        Uint32 sdl_clr = SDL_MapRGB (temp_surface->format, clr.r, clr.g, clr.b);
        SDL_SetColorKey (temp_surface, SDL_TRUE, sdl_clr);
    }


    SDL_Texture* texture = SDL_CreateTextureFromSurface (game->output.renderer, temp_surface);
    SDL_FreeSurface (temp_surface);

    if (!texture) LOG_MESSAGE ("Unable to create texture!");


    return texture;
}


//--------------------------------------------------
// PLATFORM PART START

#define DEF_SKIN(number, path, def_texture_offset, def_types, def_hitbox)     \
{                                                                             \
    Platform_Skin skin = {};                                                  \
    array_ctor (&skin.hitbox,         AET_HITBOX_RECT);                       \
    array_ctor (&skin.platform_types, AET_PLATFORM_TYPE);                     \
    skin.texture = game_get_sdl_texture (game, "media/" path);                \
    def_types                                                                 \
    def_texture_offset                                                        \
    def_hitbox                                                                \
                                                                              \
    array_push (&game->engine.platforms.skins, skin);                         \
                                                                              \
    platforms_data_update_cur_skins (&game->engine.platforms.data,            \
                 skin.platform_types, game->engine.platforms.skins.size - 1); \
}

#define DEF_PLATFORM_TYPE(type)              \
{                                            \
    array_push (&skin.platform_types, type); \
}

#define DEF_TEXTURE_OFFSET(x, y, w, h)  \
{                                       \
    skin.texture_offset = {x, y, w, h}; \
}

#define DEF_HITBOX_RECT(x, y, w, h)  \
{                                    \
    Hitbox_Rect rect = {x, y, w, h}; \
    array_push (&skin.hitbox, rect); \
}


Return_code game_load_platform_skins (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    #include "../../data/platform_skins.hpp"


    return SUCCESS;
}

#undef DEF_HITBOX_RECT
#undef DEF_TEXTURE_OFFSET
#undef DEF_SKIN
// PLATFORM PART END
//--------------------------------------------------


//--------------------------------------------------
// BACKGROUND PART START

#define DEF_BACKGROUND(number, path, flag, ...)                                               \
{                                                                                             \
    SDL_Texture* texture = game_get_sdl_texture (game, "media/" path, flag, { __VA_ARGS__ }); \
    array_push (&game->media.background_textures, texture);                                   \
}

Return_code game_load_background_textures (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    #include "../../data/backgrounds.hpp"


    return SUCCESS;
}

// BACKGROUND PART END
//--------------------------------------------------


//--------------------------------------------------
// PLAYER PART START

#define DEF_SKIN(number, path, facing, def_texture_offset, def_hitboxes) \
{                                                                        \
    Player_Skin skin = {};                                               \
    array_ctor (&skin.legs_hitbox, AET_HITBOX_RECT);                     \
    array_ctor (&skin.good_hitbox, AET_HITBOX_RECT);                     \
    skin.texture = game_get_sdl_texture (game, "media/" path);           \
    skin.default_face_direction = facing;                                \
    def_texture_offset                                                   \
    def_hitboxes                                                         \
                                                                         \
    array_push (&game->engine.players.skins, skin);                      \
}

#define DEF_TEXTURE_OFFSET(x, y, w, h)  \
{                                       \
    skin.texture_offset = {x, y, w, h}; \
}

#define DEF_LEGS_HITBOX_RECT(x, y, w, h)  \
{                                         \
    Hitbox_Rect rect = {x, y, w, h};      \
    array_push (&skin.legs_hitbox, rect); \
}

#define DEF_GOOD_HITBOX_RECT(x, y, w, h)  \
{                                         \
    Hitbox_Rect rect = {x, y, w, h};      \
    array_push (&skin.good_hitbox, rect); \
}


Return_code game_load_player_skins (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    #include "../../data/player_skins.hpp"


    return SUCCESS;
}

// PLAYER PART END
//--------------------------------------------------

