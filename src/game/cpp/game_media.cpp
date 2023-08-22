

//--------------------------------------------------


#include "../hpp/game.hpp"


//--------------------------------------------------


Return_code game_load_media (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_load_background_textures (game);
    game_load_doodler_textures    (game);
    game_load_platform_textures   (game);


    return SUCCESS;
}


Return_code game_media_push_doodler_texture (Game_Media* media, SDL_Texture* texture) {

    if (!media)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!texture) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (DEFAULT_DOODLER_TEXTURES_COUNT == media->doodler_textures_count) { LOG_ERROR (CRITICAL); return CRITICAL; }


    media->doodler_textures [media->doodler_textures_count] = texture;
    media->doodler_textures_count += 1;


    return SUCCESS;
}

/*
Return_code game_media_push_platform_texture (Game_Media* media, SDL_Texture* texture) {

    if (!media)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!texture) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (DEFAULT_PLATFORM_TEXTURES_COUNT == media->platform_textures_count) { LOG_ERROR (CRITICAL); return CRITICAL; }


    media->platform_textures [media->platform_textures_count] = texture;
    media->platform_textures_count += 1;


    return SUCCESS;
}
*/

Return_code game_media_push_background_texture (Game_Media* media, SDL_Texture* texture) {

    if (!media)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!texture) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (DEFAULT_BACKGROUND_TEXTURES_COUNT == media->background_textures_count) { LOG_ERROR (CRITICAL); return CRITICAL; }


    media->background_textures [media->background_textures_count] = texture;
    media->background_textures_count += 1;


    return SUCCESS;
}


Return_code game_load_doodler_texture (Game* game, const char* path) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!path) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* texture = game_get_sdl_texture (game, path);


    game_media_push_doodler_texture (&game->media, texture);


    return SUCCESS;
}


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


    game_media_push_background_texture (&game->media, texture);


    return SUCCESS;
}


SDL_Texture* game_get_sdl_texture (Game* game, const char* path) {

    if (!path) { LOG_ERROR (BAD_ARGS); return nullptr; }


    SDL_Surface* temp_surface = IMG_Load (path);

    if(!temp_surface) {

        LOG_MESSAGE ("Unable to load image!\n");
        return nullptr;
    }


    SDL_Texture* texture = SDL_CreateTextureFromSurface (game->output.renderer, temp_surface);
    SDL_FreeSurface (temp_surface);

    if (!texture) LOG_MESSAGE ("Unable to create texture!");


    return texture;
}


//--------------------------------------------------
#define LOAD_DOODLER(x)    game_load_doodler_texture    (game, x)
#define LOAD_PLATFORM(x)   game_load_platform_texture   (game, x)
#define LOAD_BACKGROUND(x) game_load_background_texture (game, x)

Return_code game_load_doodler_textures (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    LOAD_DOODLER (DOODLER_SKIN1_PATH);
    LOAD_DOODLER (DOODLER_SKIN2_PATH);
    LOAD_DOODLER (DOODLER_SKIN3_PATH);


    return SUCCESS;
}


Return_code game_load_platform_textures (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    LOAD_PLATFORM (PLATFORM_SKIN1_PATH);
    LOAD_PLATFORM (PLATFORM_SKIN2_PATH);
    LOAD_PLATFORM (PLATFORM_SKIN3_PATH);


    return SUCCESS;
}


Return_code game_load_background_textures (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    LOAD_BACKGROUND (BACKGROUND1_PATH);
    LOAD_BACKGROUND (BACKGROUND2_PATH);


    return SUCCESS;
}

#undef LOAD_DOODLER
#undef LOAD_PLATFORM
//--------------------------------------------------


