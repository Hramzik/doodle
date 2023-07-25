


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

    for (size_t i = 0; i < game->engine.players.count; i++) {

        game_render_player (game, &game->engine.players.buffer [i]);
    }


    return SUCCESS;
}


Return_code game_render_platforms (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < game->engine.platforms.count; i++) {

        game_render_platform (game, &game->engine.platforms.buffer [i]);
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


    SDL_Texture* platform_texture = game->media.platform_textures [0]; // TEMPORARY
    if (platform->type == PT_CLOUD) platform_texture = game->media.platform_textures [1];


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


