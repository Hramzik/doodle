

//--------------------------------------------------

#include "../hpp/engine.hpp"

//--------------------------------------------------


Object_Motion static_motion (double x, double y) {

    Object_Motion motion;

    motion.x = x;
    motion.y = y;

    motion.dx  = 0;
    motion.dy  = 0;
    motion.ddx = 0;
    motion.ddy = 0;


    return motion;
}


Object_Motion linear_motion (double x, double y, double dx, double dy) {

    Object_Motion motion;

    motion.x = x;
    motion.y = y;

    motion.dx  = dx;
    motion.dy  = dy;
    motion.ddx = 0;
    motion.ddy = 0;


    return motion;
}


Object_Motion linear_dynamics (double dx, double dy) {

    Object_Motion motion;

    motion.x = 0;
    motion.y = 0;

    motion.dx  = dx;
    motion.dy  = dy;
    motion.ddx = 0;
    motion.ddy = 0;


    return motion;
}


Object_Motion quadratic_dynamics (double dx, double dy, double ddx, double ddy) {

    Object_Motion motion;

    motion.x = 0;
    motion.y = 0;

    motion.dx  = dx;
    motion.dy  = dy;
    motion.ddx = ddx;
    motion.ddy = ddy;


    return motion;
}


Return_code engine_check_collisions (Game_Engine* engine) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < engine->players.count; i++) {

        engine_check_player_collisions (engine, &engine->players.buffer [i]);
    }


    return SUCCESS;
}


Return_code engine_check_player_collisions (Game_Engine* engine, Player* player) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (player->motion.dy > 0) return SUCCESS; // летит вверх


    for (size_t i = 0; i < engine->platforms.count; i++) {

        engine_check_player_platform_collision (engine, player, i);
    }


    return SUCCESS;
}


Return_code engine_check_player_platform_collision (Game_Engine* engine, Player* player, size_t platform_ind) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!player)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Platform* platform = &engine->platforms.buffer [platform_ind];


    if (player  ->motion.x + DOODLER_WIDTH  / 2 < platform->motion.x - PLATFORM_WIDTH / 2 ||
        platform->motion.x + PLATFORM_WIDTH / 2 < player  ->motion.x - DOODLER_WIDTH  / 2) return SUCCESS;

    if (player->motion.y < platform->motion.y ||
        player->motion.y > platform->motion.y + PLATFORM_HEIGHT) return SUCCESS;


    //printf ("debug: passed point COLLISION REGISTERED!\n");
    player->platform_hit_ind = (int) platform_ind;


    return SUCCESS;
}


Return_code engine_move_objects (Game_Engine* engine) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    engine_move_players      (engine);
    //engine_move_playtforms (engine);


    return SUCCESS;
}


Return_code engine_move_players (Game_Engine* engine) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < engine->players.count; i++) {

        engine_move_player (engine, &engine->players.buffer [i]);
    }


    return SUCCESS;
}


Return_code engine_move_player (Game_Engine* engine, Player* player) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (player->platform_hit_ind == -1) {

        player_move_no_collision (player, engine->data.t);
        return SUCCESS;
    }


    player_move_collision (player, &engine->platforms.buffer [player->platform_hit_ind], engine->data.t);


    return SUCCESS;
}


Return_code player_move_no_collision (Player* player, double t) {

    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Object_Motion* motion = &player->motion;
    motion->x  += motion->dx  * t + motion->ddx * t * t / 2;
    motion->y  += motion->dy  * t + motion->ddy * t * t / 2;
    motion->dx += motion->ddx * t;
    motion->dy += motion->ddy * t;


    return SUCCESS;
}


Return_code player_move_collision (Player* player, Platform* platform, double t) {

    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Object_Motion* motion = &player->motion;
    motion->dy = PLAYER_DY_AFTER_COLLISION;

    motion->x  += motion->dx  * t;
    motion->y  += motion->dy  * t;
    motion->dx += motion->ddx * t;
    motion->dy += motion->ddy * t;


    (void) platform; // cloud


    player->platform_hit_ind = -1;


    return SUCCESS;
}


