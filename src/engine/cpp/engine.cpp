

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


Return_code motion_copy_dynamics (Object_Motion src, Object_Motion* dst) {

    if (!dst) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    dst->dx  = src.dx;
    dst->dy  = src.dy;
    dst->ddx = src.ddx;
    dst->ddy = src.ddy;


    return SUCCESS;
}


Return_code motion_copy_dynamics (Object_Motion* src, Object_Motion* dst) {

    if (!src) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!dst) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return motion_copy_dynamics (*src, dst);
}


Platform* engine_check_player_collisions (Game_Engine* engine, Player* player) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return nullptr; }
    if (!player) { LOG_ERROR (BAD_ARGS); return nullptr; }


    if (player->motion.dy >= 0) return nullptr;


    for (Node* node = engine->platforms.list.first; node; node = node->next) {

        Platform* platform = node_get_platform (node);


        if (!check_player_platform_collision (*player, *platform)) continue;


        if (platform->type == PT_FAKE)  { platform->dead = true; continue; }
        if (platform->type == PT_CLOUD)   platform->dead = true;


        return platform;
    }


    return nullptr;
}


bool check_player_platform_collision (Player player, Platform platform) {

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


    for (size_t i = 0; i < engine->players.list.len; i++) {

        engine_move_player (engine, list_get_player (engine->players.list, i));
    }


    return SUCCESS;
}


Return_code engine_move_player (Game_Engine* engine, Player* player) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Platform* platform = engine_check_player_collisions (engine, player);


    if (!platform) {

        player_move_no_collision (player, engine->data.t);
        return SUCCESS;
    }


    player_move_collision (player, platform, engine->data.t);


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


    (void) platform; // было для cloud, теперь хз


    return SUCCESS;
}

