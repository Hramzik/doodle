

//--------------------------------------------------


#include "../hpp/game.hpp"


//--------------------------------------------------


Return_code game_spawn_players (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (game->data.game_mode) {

        case SINGLE_PLAYER: game_spawn_player (game, DEFAULT_WINDOW_WIDTH / 2, DEFAULT_WINDOW_HEIGHT * 3 / 6, DEFAULT_PLAYER_SKIN - 1); break;
        case DUO:
        default: break;
    }


    return SUCCESS;
}


Return_code game_spawn_player (Game* game, double x, double y, size_t skin) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Object_Motion player_motion = { .x = x, .y = y, .dx = 0, .dy = DEFAULT_PLAYER_DY, .ddx = 0, .ddy = DEFAULT_PLAYER_DDY };
    Player player = { .motion = player_motion, .score = 0, .skin = skin, .platform_hit_ind = -1 };


    players_push (&game->engine.players, player);


    return SUCCESS;
}


Return_code game_work (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_load_media    (game);
    game_spawn_players (game);


    Timer* timer = timer_ctor ();


    while(true) {

    //--------------------------------------------------
        game_handle_keyboard_input (game);

        if (game->conditions.exit) break;
    //--------------------------------------------------


        game_update      (game);
        timer_next_frame (timer);


        SDL_RenderClear   (game->output.renderer);
        game_render       (game);
        SDL_RenderPresent (game->output.renderer);

        //if (timer->frame_number % 2500 == 0) player_dump (&game->engine.players.buffer [0]);
        // timer
    }


    // timer dtor


    return SUCCESS;
}



//--------------------------------------------------


Return_code game_update (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_spawn_objects (game);


    engine_check_collisions (&game->engine);


    engine_move_objects (&game->engine);
    game_mirror_players (game);
    game_move_camera    (game);


    //game_despawn_object (game);


    return SUCCESS;
}


Return_code game_spawn_objects (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    //game_spawn_players   (game);
    game_spawn_platforms (game);


    return SUCCESS;
}


Return_code game_spawn_platforms (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (game->data.game_mode) {

        case SINGLE_PLAYER: game_spawn_platforms_singleplayer (game); break;
        case DUO:
        default: break;
    }


    return SUCCESS;
}


Return_code game_move_camera (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    double min_player_y = players_get_min_player_y (&game->engine.players);


    if (game->data.camera_y + DEFAULT_WINDOW_HEIGHT / 2 < min_player_y) {

        game->data.camera_y = min_player_y - DEFAULT_WINDOW_HEIGHT / 2;
    }


    return SUCCESS;
}

Return_code game_mirror_players (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < game->engine.players.count; i++) {

        game_mirror_player (game, &game->engine.players.buffer [i]);
    }


    return SUCCESS;
}


Return_code game_mirror_player (Game* game, Player* player) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    while (player->motion.x < 0)                    player->motion.x += DEFAULT_WINDOW_WIDTH;
    while (player->motion.x > DEFAULT_WINDOW_WIDTH) player->motion.x -= DEFAULT_WINDOW_WIDTH;


    return SUCCESS;
}

