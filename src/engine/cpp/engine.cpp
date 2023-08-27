

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


        if (!engine_check_player_platform_collision (*engine, *player, *platform)) continue;


        if (platform->type == PT_FAKE)  { platform->dead = true; continue; }
        if (platform->type == PT_CLOUD)   platform->dead = true;


        return platform;
    }


    return nullptr;
}


bool engine_check_player_platform_collision
(Game_Engine engine, Player player, Platform platform)
{

    if (player.max_cur_jump_y < platform.motion.y + PLATFORM_HITBOX_HEIGHT) return false;
    // не был выше платформы


    Player_Skin skin = array_get_player_skin (engine.players.skins, player.skin);


    return does_player_overlap_platform (player, skin, platform);
}


bool does_player_overlap_platform (Player player, Player_Skin skin, Platform platform) {

    Hitbox_Rect platform_rect        = platform_get_true_hitbox_rect (platform);
    Hitbox_Rect relative_player_rect = {};
    Hitbox_Rect true_player_rect     = {};


    for (size_t i = 0; i < skin.legs_hitbox.size; i++) {

        relative_player_rect = array_get_hitbox_rect (skin.legs_hitbox, i);

        if (player.facing != skin.default_face_direction) {

            hitbox_rect_mirror_horizontally (&relative_player_rect);
        }


        true_player_rect = motion_get_true_hitbox_rect (player.motion, relative_player_rect);


        if (do_hitbox_rects_overlap (true_player_rect, platform_rect)) return true;
    }


    return false;
}



Return_code engine_update (Game_Engine* engine) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    engine_move_players   (engine);
    engine_move_platforms (engine);
    engine_update_players (engine);


    return SUCCESS;
}


bool do_hitbox_rects_overlap (Hitbox_Rect rect1, Hitbox_Rect rect2) {

    if (rect1.x + rect1.w < rect2.x) return false;
    if (rect2.x + rect2.w < rect1.x) return false;

    if (rect1.y < rect2.y - rect2.h) return false;
    if (rect2.y < rect1.y - rect1.h) return false;


    return true;
}


Return_code hitbox_rect_mirror_horizontally (Hitbox_Rect* rect) {

    if (!rect) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (rect->x >= 0) rect->x -= rect->w;
    else              rect->x += rect->w;


    rect->x *= -1;


    return SUCCESS;
}

