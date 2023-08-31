

//--------------------------------------------------

#include "../hpp/engine.hpp"
#include "../hpp/dsl.hpp"

//--------------------------------------------------


Return_code player_dump (Player* player) {

    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Object_Motion motion = player->motion;


    printf ("dumping player..\n");
    printf ("x,   y:   %5.2lf %5.2lf\n", motion.x,   motion.y);
    printf ("dx,  dy:  %5.2lf %5.2lf\n", motion.dx,  motion.dy);
    printf ("ddx, ddy: %5.2lf %5.2lf\n", motion.ddx, motion.ddy);


    return SUCCESS;
}


double players_get_min_player_y (Players* players) {

    if (!players) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    double min_player_y = 0;


    for (Node* node = players->list.first; node; node = node->next) {

        Player* player = node_get_player (node);

        if (min_player_y < player->motion.y) {

            min_player_y = player->motion.y;
        }
    }


    return min_player_y;
}


Return_code engine_move_players (Game_Engine* engine) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < engine->players.list.len; i++) {

        engine_move_player (engine, list_get_player (engine->players.list, i));
    }


    return SUCCESS;
}


Return_code engine_move_player (Game_Engine* engine, Player* player) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Platform* platform = engine_check_player_collisions (engine, player);
    if (platform) player->motion.dy = PLAYER_DY_AFTER_COLLISION;


    if (player->vertically_frozen) motion_update_x_part (&player->motion, engine->data.t);
    else                           motion_update        (&player->motion, engine->data.t);


    return ensure_player_on_screen (engine, player);
}


Return_code engine_update_players (Game_Engine* engine) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < engine->players.list.len; i++) {

        player_update (list_get_player (engine->players.list, i));
    }


    return SUCCESS;
}


Return_code player_update (Player* player) {

    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    player_facing_update        (player);
    player_max_curjump_y_update (player);


    return SUCCESS;
}


Return_code player_facing_update (Player* player) {

    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (player->motion.dx > 0) player->facing = PFD_RIGHT;
    if (player->motion.dx < 0) player->facing = PFD_LEFT;


    return SUCCESS;
}


Return_code player_max_curjump_y_update (Player* player) {

    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (player->motion.dy <= 0) return SUCCESS;


    player->max_cur_jump_y = player->motion.y;


    return SUCCESS;
}


Return_code ensure_player_on_screen (Game_Engine* engine, Player* player) {

    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    while (player->motion.x < 0)           player->motion.x += ENGINE_FIELD_WIDTH;
    while (player->motion.x > ENGINE_FIELD_WIDTH) player->motion.x -= ENGINE_FIELD_WIDTH;


    return SUCCESS;
}

