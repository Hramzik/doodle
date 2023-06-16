

//--------------------------------------------------

#include "../hpp/singleplayer.hpp"

//--------------------------------------------------



Return_code spawn_platform_difficulty_0 (Game* game, Platform_type type) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (type) {

        case PT_DEFAULT: return spawn_default_platform (game);
        case PT_MOVING:  return spawn_moving_platform  (game);
        case PT_CLOUD:   return spawn_cloud_platform   (game);
        case PT_FAKE:    return spawn_fake_platform    (game);
        default: break;
    }


    return SUCCESS;
}


static Return_code spawn_default_platform (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return spawn_default_platform (game, DIFFICULTY_0_MIN_PLATFORM_GAP, DIFFICULTY_0_MAX_PLATFORM_GAP);
}

