

//--------------------------------------------------


#include "../hpp/game.hpp"


//--------------------------------------------------


Return_code game_load_media (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_load_background_textures (game);
    game_load_player_skins        (game);
    game_load_platform_textures   (game);


    return SUCCESS;
}


/*
Return_code game_load_doodler_texture (Game* game, const char* path) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!path) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* texture = game_get_sdl_texture (game, path);


    array_push (&game->media.player_textures, texture);


    return SUCCESS;
}*/


Return_code game_load_platform_texture (Game* game, const char* path) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!path) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* texture = game_get_sdl_texture (game, path);

    array_push (&game->media.platform_textures, texture);


    return SUCCESS;
}


Return_code game_load_background_texture (Game* game, const char* path) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!path) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* texture = game_get_sdl_texture (game, path);


    array_push (&game->media.background_textures, texture);


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
#define LOAD_PLATFORM(x)   game_load_platform_texture   (game, x)
#define LOAD_BACKGROUND(x) game_load_background_texture (game, x)


Return_code game_load_platform_textures (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    LOAD_PLATFORM (PLATFORM_SKIN1_PATH);
    LOAD_PLATFORM (PLATFORM_SKIN2_PATH);
    LOAD_PLATFORM (PLATFORM_SKIN3_PATH);


    return SUCCESS;
}


//--------------------------------------------------
#define DEF_BACKGROUND(number, path, flag, ...)                                               \
{                                                                                             \
    SDL_Texture* texture = game_get_sdl_texture (game, "media/" path, flag, { __VA_ARGS__ }); \
    array_push (&game->media.background_textures, texture);                                   \
}

Return_code game_load_background_textures (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    #include "../../common/backgrounds.hpp"


    return SUCCESS;
}
//--------------------------------------------------


//--------------------------------------------------
#define DEF_SKIN(number, path, def_texture_offset, def_platform_hitboxes, def_good_hitboxes) \
{                                                                \
    Player_Skin skin = {};                                       \
    array_ctor (&skin.legs_hitbox, AET_HITBOX_RECT);             \
    array_ctor (&skin.good_hitbox, AET_HITBOX_RECT);             \
    skin.texture = game_get_sdl_texture (game, "media/" path);   \
    def_texture_offset                                           \
    def_platform_hitboxes                                        \
    def_good_hitboxes                                            \
                                                                 \
    array_push (&game->engine.players.skins, skin);              \
}

#define DEF_TEXTURE_OFFSET(x, y, w, h)  \
{                                       \
    skin.texture_offset = {x, y, w, h}; \
} \

#define DEF_LEGS_HITBOX_RECT(x, y, w, h)   \
{                                             \
    Hitbox_Rect rect = {x, y, w, h};          \
    array_push (&skin.legs_hitbox, rect); \
}

#define DEF_GOOD_HITBOX_RECT(x, y, w, h)  \
{                                         \
    Hitbox_Rect rect = {x, y, w, h};      \
    array_push (&skin.good_hitbox, rect); \
}


Return_code game_load_player_skins (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    #include "../../common/player_skins.hpp"


    return SUCCESS;
}
//--------------------------------------------------

