

//--------------------------------------------------


#include "../hpp/game.hpp"


//--------------------------------------------------


Return_code game_media_push_doodler_texture (Game_Media* media, SDL_Texture* texture) {

    if (!media)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!texture) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (DEFAULT_DOODLER_TEXTURES_COUNT == media->doodler_textures_count) { LOG_ERROR (CRITICAL); return CRITICAL; }


    media->doodler_textures [media->doodler_textures_count] = texture;
    media->doodler_textures_count += 1;


    return SUCCESS;
}


Return_code game_media_push_platform_texture (Game_Media* media, SDL_Texture* texture) {

    if (!media)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!texture) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (DEFAULT_PLATFORM_TEXTURES_COUNT == media->platform_textures_count) { LOG_ERROR (CRITICAL); return CRITICAL; }


    media->platform_textures [media->platform_textures_count] = texture;
    media->platform_textures_count += 1;


    return SUCCESS;
}


Return_code game_load_doodler_texture (Game* game, const char* path) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!path) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Surface* temp_surface = IMG_Load (path); // unformatted, slow

    if(!temp_surface) {

        LOG_MESSAGE ("Unable to load image!\n");
        return LIB_ERR;
    }


    SDL_Texture* new_texture = SDL_CreateTextureFromSurface (crack->crack_window->renderer, temp_surface);
    SDL_FreeSurface (temp_surface);

    if (!new_texture) {

        LOG_MESSAGE ("Unable to create texture!");
        return LIB_ERR;
    }


    game_media_push_doodler_texture (&game->media, new_texture);


    return SUCCESS;
}


Return_code game_load_platform_texture (Game* game, const char* path) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!path) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Surface* temp_surface = IMG_Load (path); // unformatted, slow

    if(!temp_surface) {

        LOG_MESSAGE ("Unable to load image!\n");
        return LIB_ERR;
    }


    SDL_Texture* new_texture = SDL_CreateTextureFromSurface (crack->crack_window->renderer, temp_surface);
    SDL_FreeSurface (temp_surface);

    if (!new_texture) {

        LOG_MESSAGE ("Unable to create texture!");
        return LIB_ERR;
    }


    game_media_push_platform_texture (&game->media, new_texture);


    return SUCCESS;
}


//--------------------------------------------------
#define LOAD_DOODLER(x)  game_load_doodler_texture  (game, x)
#define LOAD_PLATFORM(x) game_load_platform_texture (game, x)

Return_code game_load_doodler_textures (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    LOAD_DOODLER (DOODLER_SKIN1_PATH);


    LOAD_PLATFORM (PLATFORM_SKIN1_PATH);


    return SUCCESS;
}

#undef LOAD_DOODLER
#undef LOAD_PLATFORM
//--------------------------------------------------

