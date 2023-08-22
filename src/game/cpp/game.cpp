

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


        game_clear_screen (game);
        game_render       (game);
        SDL_RenderPresent (game->output.renderer);

        timer_next_frame (timer);


        game->engine.data.t = DEFAULT_UPDATE_TIME * 4.5 * timer_get_last_frame_delay_ms (timer);


        if ((size_t) timer_get_total_delay_ms (timer) % 10000 == 0) {

            printf ("score: %.0lf\n", list_get_player (game->engine.players.list, 0)->score);
            player_dump (list_get_player (game->engine.players.list, 0));
            //timer_print_fps (timer);
        }
    }


    timer_dtor (timer);


    return SUCCESS;
}



//--------------------------------------------------


Return_code game_update (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    double updated_time = 0;
    double needed_update_time = game->engine.data.t;


    game->engine.data.t = MAX_UPDATE_TIME;

    for (; updated_time + MAX_UPDATE_TIME <= needed_update_time; updated_time += MAX_UPDATE_TIME) {

        game_update_no_time_control (game);
    }


    game->engine.data.t = needed_update_time - updated_time;
    game_update_no_time_control (game);


    game->engine.data.t = needed_update_time;


    return SUCCESS;
}


Return_code game_update_no_time_control (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_spawn_objects (game);


    engine_update       (&game->engine);
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


    Node* next_node = nullptr;

    for (Node* node = list->first; node; node = next_node) {

        next_node = node->next;

        if (node_get_platform (node)->dead) {

            list_delete (list, node);
            continue;
        }

        if (node_get_platform (node)->motion.y + PLATFORM_TEXTURE_HEIGHT < game->data.camera_y) {

            list_delete (list, node);
            continue;
        }
    }


    return SUCCESS;
}


Return_code game_move_camera (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    double old_camera_y = game->data.camera_y;
    double min_player_y = players_get_min_player_y (&game->engine.players);


    if (game->data.camera_y + DEFAULT_FIELD_HEIGHT * 0.4 < min_player_y) {

        game->data.camera_y = min_player_y - DEFAULT_FIELD_HEIGHT * 0.4;

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


double random_scale (double input) {

    return (double) rand () / RAND_MAX * input;
}

/*
Return_code check_global_constants (void) {

    return SUCCESS;
}

*/