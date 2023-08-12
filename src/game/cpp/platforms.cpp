

//--------------------------------------------------

#include "../hpp/game.hpp"

//--------------------------------------------------


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



Platform generate_static_platform (Game* game, Point gaps, Platform_type type) {

    if (!game) LOG_ERROR (BAD_ARGS);


    double min_x = PLATFORM_TEXTURE_WIDTH / 2;
    double     x = min_x + random_scale (DEFAULT_WINDOW_WIDTH - PLATFORM_TEXTURE_WIDTH);

    double min_y = gaps.min + MAX_Y;
    double     y = min_y + random_scale (gaps.max - gaps.min);


    Object_Motion motion   = static_motion (x, y);
    Platform      platform = { .motion = motion, .type = type, .dead = false };


    return platform;
}


Return_code spawn_static_platform (Game* game, Point gaps, Platform_type type) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Platform platform = generate_static_platform (game, gaps, type);
    game_add_platform (game, platform);


    return SUCCESS;
}


Return_code spawn_moving_platform (Game* game, Point gaps, Object_Motion dynamics, Platform_type type) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Platform platform = generate_static_platform (game, gaps, type);
    motion_copy_dynamics (dynamics, &platform.motion);
    game_add_platform (game, platform);


    return SUCCESS;
}

