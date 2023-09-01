

//--------------------------------------------------


#include "../hpp/game.hpp"


//--------------------------------------------------


static bool node_is_platform_dead                   (Node node);
static bool node_is_platform_off_screen (Game* game, Node node);


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


    SDL_Rect texture_offset = engine_get_platform_type_skin (game->engine, type).texture_offset;
    double min_x = - texture_offset.x;
    double     x = min_x + random_scale (GAME_WINDOW_WIDTH - texture_offset.w);

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


Return_code game_despawn_platforms (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    List* list = &game->engine.platforms.list;


    Node* next_node = nullptr;
    bool  delete_flag = false;


    for (Node* node = list->first; node; node = next_node) {

        next_node   = node->next;

        delete_flag  = false;
        delete_flag |= node_is_platform_dead             (*node);
        delete_flag |= node_is_platform_off_screen (game, *node);

        if (delete_flag) list_delete (list, node);
    }


    return SUCCESS;
}


static bool node_is_platform_dead (Node node) {

    if (node_get_platform (node)->dead) return true;


    return false;
}


static bool node_is_platform_off_screen (Game* game, Node node) {

    if (!game) { LOG_ERROR (BAD_ARGS); return false; }


    Platform* platform         = node_get_platform (node);
    double    texture_y_offset = engine_get_platform_skin (game->engine, *platform).texture_offset.y;


    if (platform->motion.y + texture_y_offset < game->data.camera_y) return true;


    return false;
}
