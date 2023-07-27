

//--------------------------------------------------


#include "../hpp/game.hpp"


//--------------------------------------------------


Return_code game_spawn_players (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (game->data.game_mode) {

        case SINGLE_PLAYER: game_spawn_players_singleplayer (game); break;
        case DUO:
        default: break;
    }


    return SUCCESS;
}


Return_code game_add_player (Game* game, Player player) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_push_back (&game->engine.players.list, player);


    return SUCCESS;
}


Return_code game_add_platform (Game* game, Platform platform) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_push_back (&game->engine.platforms.list, platform);
    update_max_y (game, platform);


    return SUCCESS;
}


Return_code update_max_y (Game* game, Platform platform) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (PLATFORM_Y > MAX_Y) MAX_Y = PLATFORM_Y;
    if (platform.type == PT_FAKE) return SUCCESS;

    if (PLATFORM_Y > MAX_MATERIAL_Y) MAX_MATERIAL_Y = PLATFORM_Y;


    return SUCCESS;
}


Return_code game_work (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_load_media (game);
    Timer* timer = timer_ctor ();


    while(true) {

    //--------------------------------------------------
        game_handle_keyboard_input (game);

        if (game->conditions.exit) break;
    //--------------------------------------------------


        game_update (game);


        SDL_RenderClear   (game->output.renderer);
        game_render       (game);
        SDL_RenderPresent (game->output.renderer);

        timer_next_frame (timer);


        game->engine.data.t = DEFAULT_UPDATE_TIME * 4.5 * timer_get_last_frame_delay_ms (timer);


        if ((size_t) timer_get_total_delay_ms (timer) % 10000 == 0) {

            printf ("score: %lf\n", list_get_player (game->engine.players.list, 0)->score);
            //timer_print_fps (timer);
        }
    }


    timer_dtor (timer);


    return SUCCESS;
}



//--------------------------------------------------


Return_code game_update (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_spawn_objects (game);


    engine_move_objects (&game->engine);
    game_mirror_players (game);
    game_move_camera    (game);


    game_despawn_objects (game);


    return SUCCESS;
}


Return_code game_spawn_objects (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_spawn_players   (game);
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


Return_code game_despawn_objects (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    //game_spawn_players   (game);
    game_despawn_platforms (game);


    return SUCCESS;
}


Return_code game_despawn_platforms (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    List* list = &game->engine.platforms.list;

    for (Node* node = list->first; node; ) {

        Node* next_node = node->next;

        if (node_get_platform (node)->dead) list_delete (list, node);


        node = next_node;
    }


    return SUCCESS;
}


Return_code game_move_camera (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    double old_camera_y = game->data.camera_y;
    double min_player_y = players_get_min_player_y (&game->engine.players);


    if (game->data.camera_y + DEFAULT_WINDOW_HEIGHT / 2 < min_player_y) {

        game->data.camera_y = min_player_y - DEFAULT_WINDOW_HEIGHT / 2;

        game_update_scores_camera_y (game, game->data.camera_y - old_camera_y);
    }


    return SUCCESS;
}


Return_code game_update_scores_camera_y (Game* game, double camera_disance) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (game->data.game_mode) {

        case SINGLE_PLAYER: game_update_scores_camera_y_singleplayer (game, camera_disance); break;
        case DUO:
        default: CODE_CRITICAL;
    }


    return SUCCESS;
}


Return_code game_mirror_players (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < game->engine.players.list.len; i++) {

        game_mirror_player (game, list_get_player (game->engine.players.list, i));
    }


    return SUCCESS;
}


Return_code game_mirror_player (Game* game, Player* player) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    while (player->motion.x < 0)                    player->motion.x += DEFAULT_WINDOW_WIDTH;
    while (player->motion.x > DEFAULT_WINDOW_WIDTH) player->motion.x -= DEFAULT_WINDOW_WIDTH;


    return SUCCESS;
}


double random_scale (double input) {

    return (double) rand () / RAND_MAX * input;
}

/*
Return_code check_global_constants (void) {

    return SUCCESS;
}

*/