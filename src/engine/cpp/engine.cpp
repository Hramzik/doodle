

//--------------------------------------------------

#include "../hpp/engine.hpp"
#include "../hpp/dsl_on.hpp"

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


Platform* engine_check_player_collisions (Game_Engine* engine, Player* player) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (player->motion.dy > 0) return SUCCESS; // летит вверх


    for (size_t i = 0; i < engine->platforms.count; i++) {

        engine_check_player_platform_collision (engine, player, i);
    }


    return SUCCESS;
}


bool check_player_platform_collision (Player* player, Platform* platform) {

    if (PLAYER_X   + DOODLER_HITBOX_RIGHT_WIDTH / 2 < PLATFORM_X - PLATFORM_WIDTH            / 2 ||
        PLATFORM_X + PLATFORM_WIDTH             / 2 < PLAYER_X   - DOODLER_HITBOX_LEFT_WIDTH / 2) return false;

    if (PLAYER_Y < PLATFORM_Y ||
        PLAYER_Y > PLATFORM_Y + PLATFORM_HEIGHT) return false;


    return true;
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

        engine_move_player (engine, list_get_player (engine->players.list, i));
    }


    return SUCCESS;
}


Return_code engine_move_player (Game_Engine* engine, Player* player) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    bool      collision_flag = false;
    Platform* cur_platform   = nullptr;
    Platform* hit_platform   = nullptr;

    for (size_t i = 0; i < engine->platforms.count; i++) {

        cur_platform = &engine->platforms.buffer [i];
        collision_flag = engine_check_player_platform_collision (player, cur_platform);

        if (!collision_flag) continue;


        if (cur_platform->type == PT_FAKE) { engine_destroy_fake_platform (engine, cur_platform); continue; }


        hit_platform = cur_platform;
    }


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

