

//--------------------------------------------------

#include "../hpp/engine.hpp"
#include "../hpp/dsl.hpp"

//--------------------------------------------------



Return_code engine_move_platforms (Game_Engine* engine) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < engine->platforms.list.len; i++) {

        engine_move_platform (engine, list_get_platform (engine->platforms.list, i));
    }


    return SUCCESS;
}


Return_code engine_move_platform (Game_Engine* engine, Platform* platform) {

    if (!engine)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!platform) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    motion_update (&platform->motion, engine->data.t);


    return ensure_platform_on_screen (engine, platform);
}


Return_code ensure_platform_on_screen (Game_Engine* engine, Platform* platform) {

    if (!engine)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!platform) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    motion_ensure_x_ge_than (&platform->motion, PLATFORM_HITBOX_WIDTH / 2);
    motion_ensure_x_le_than (&platform->motion, FIELD_WIDTH - PLATFORM_HITBOX_WIDTH / 2);


    return SUCCESS;
}

