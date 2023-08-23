

//--------------------------------------------------

#include "../hpp/engine.hpp"
#include "../hpp/dsl.hpp"

//--------------------------------------------------


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

    if (player.max_cur_jump_y < platform.motion.y + PLATFORM_HITBOX_HEIGHT) return false;
    // не был выше платформы

    return do_hitboxes_overlap (get_skin_hitbox)


    return true;
}


Return_code engine_update (Game_Engine* engine) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    engine_move_players   (engine);
    engine_move_platforms (engine);
    engine_update_players (engine);


    return SUCCESS;
}


