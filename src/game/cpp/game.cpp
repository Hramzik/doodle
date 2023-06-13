

//--------------------------------------------------


#include "../hpp/game.hpp"


//--------------------------------------------------


Return_code game_load_media (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_load_doodler_textures  (game);
    game_load_platform_textures (game);


    return SUCCESS;
}


Return_code game_spawn_players (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (game->data.game_mode) {

        case SINGLE_PLAYER: game_spawn_player (game, DEFAULT_WINDOW_WIDTH / 2, 10, DEFAULT_PLAYER_SKIN);
        case DUO:
        default:
    }


    return SUCCESS;
}


Return_code game_spawn_player (Game* game, double x, double y, size_t skin) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Object_Motion player_motion = { .x = x, .y = y, .dx = 0, .dy = DEFAULT_PLAYER_DY, .ddx = 0, .ddy = DEFAULT_PLAYER_DDY };
    Player player = { .motion = player_motion, .score = 0, .skin = skin };


    players_push (game->field.players, player);


    return SUCCESS;
}


Return_code game_work (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_load_media    (game);
    game_spawn_players (game);


    while(true) {

    //--------------------------------------------------
        game_handle_keyboard_input (game);

        if (game->conditions.exit) break;
    //--------------------------------------------------


        // engine call


        SDL_RenderClear   (game->output.renderer);
        game_render       (game);
        SDL_RenderPresent (game->output.renderer);


        // timer
    }


    // timer dtor


    return SUCCESS;
}


Return_code game_render (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < game->field.players.count; i++) {

        game_render_player (game, &game->field.players.buffer [i]);
    }

    for (size_t i = 0; i < game->field.platforms.count; i++) {

        game_render_platform (game, &game->field.platforms.buffer [i]);
    }


    return SUCCESS;
}



Return_code game_render_player (Game* game, Player* player) {

    if (!game)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* player_texture = game->media.doodler_textures [player->skin];
    SDL_Rect dstrect = { .x = player->motion.x - DOODLER_WIDTH / 2, .y = player->motion.y, .w = DOODLER_WIDTH, .h = DOODLER_HEIGHT };


    SDL_RenderCopy (game->output.renderer, player_texture, nullptr, dstrect);


    return SUCCESS;
}


Return_code game_render_platform (Game* game, Platform* platform) {

    if (!game)     { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!platform) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* platform_texture = game->media.platform_textures [0]; // TEMPORARY
    SDL_Rect dstrect = { .x = platform->motion.x - PLATFORM_WIDTH / 2, .y = platform->motion.y, .w = PLATFORM_WIDTH, .h = PLATFORM_HEIGHT };


    SDL_RenderCopy (game->output.renderer, platform_texture, nullptr, dstrect);


    return SUCCESS;
}


