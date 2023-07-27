


//--------------------------------------------------

#include "../hpp/game.hpp"

//--------------------------------------------------



Return_code game_render (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_render_background (game);
    game_render_platforms  (game);
    game_render_players    (game);


    return SUCCESS;
}


Return_code game_render_players (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }

    for (size_t i = 0; i < game->engine.players.list.len; i++) {

        game_render_player (game, list_get_player (game->engine.players.list, i));
    }


    return SUCCESS;
}


Return_code game_render_platforms (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < game->engine.platforms.list.len; i++) {

        game_render_platform (game, list_get_platform (game->engine.platforms.list, i));
    }


    return SUCCESS;
}


Return_code game_render_player (Game* game, Player* player) {

    if (!game)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* player_texture = game->media.doodler_textures [player->skin];
    SDL_Rect dstrect;

    dstrect.x = (int) player->motion.x - DOODLER_TEXTURE_WIDTH / 2;
    dstrect.y = (int) game->data.camera_y + DEFAULT_WINDOW_HEIGHT - (int) player->motion.y - DOODLER_TEXTURE_HEIGHT;
    dstrect.w = DOODLER_TEXTURE_WIDTH;
    dstrect.h = DOODLER_TEXTURE_HEIGHT;


    SDL_RenderCopy (game->output.renderer, player_texture, nullptr, &dstrect);


    return SUCCESS;
}


Return_code game_render_platform (Game* game, Platform* platform) {

    if (!game)     { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!platform) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* platform_texture = game_get_platform_texture (game, platform);


    SDL_Rect dstrect;

    dstrect.x = (int) platform->motion.x - PLATFORM_WIDTH / 2;
    dstrect.y = (int) game->data.camera_y + DEFAULT_WINDOW_HEIGHT - (int) platform->motion.y - PLATFORM_HEIGHT;
    dstrect.w = PLATFORM_WIDTH;
    dstrect.h = PLATFORM_HEIGHT;

    SDL_RenderCopy (game->output.renderer, platform_texture, nullptr, &dstrect);


    return SUCCESS;
}


Return_code game_render_background (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* background_texture = game->media.background_textures [0]; // TEMPORARY
    SDL_Rect srcrect;

    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = DEFAULT_WINDOW_WIDTH;
    srcrect.h = DEFAULT_WINDOW_HEIGHT;


    SDL_RenderCopy (game->output.renderer, background_texture, &srcrect, nullptr);


    return SUCCESS;
}


SDL_Texture* game_get_platform_texture (Game* game, Platform* platform) {

    if (!game)     { LOG_ERROR (BAD_ARGS); return nullptr; }
    if (!platform) { LOG_ERROR (BAD_ARGS); return nullptr; }


    switch (platform->type) {

        case PT_DEFAULT: return game->media.platform_textures [0];
        case PT_FAKE:    return game->media.platform_textures [1];
        case PT_MOVING:  return game->media.platform_textures [0];
        case PT_CLOUD:   return game->media.platform_textures [2];

        default: LOG_ERROR (CRITICAL); return nullptr;
    }
}

