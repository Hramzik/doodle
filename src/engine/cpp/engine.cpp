

//--------------------------------------------------

#include "../hpp/engine.hpp"
#include "../hpp/dsl.hpp"

//--------------------------------------------------


static bool engine_check_player_platform_collision
    (Game_Engine engine, Player player, Platform platform);

bool does_player_overlap_platform
    (Player player, Player_Skin player_skin, Platform platform, Platform_Skin platform_skin);

static bool does_hitbox_overlap_true_hitbox_rect
    (Object_Motion coords, Array hitbox, Hitbox_Rect true_rect);

static bool do_hitbox_rects_overlap (Hitbox_Rect rect1, Hitbox_Rect rect2);


//--------------------------------------------------


Return_code engine_update (Game_Engine* engine) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    engine_move_players   (engine);
    engine_move_platforms (engine);
    engine_update_players (engine);


    return SUCCESS;
}


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


static bool engine_check_player_platform_collision
(Game_Engine engine, Player player, Platform platform)
{

    Player_Skin   player_skin = array_get_player_skin    (engine.players.skins, player.skin);
    Platform_Skin platform_skin = engine_get_platform_skin (engine, platform);


    if (player.max_cur_jump_y < platform.motion.y + platform_skin.texture_offset.y) return false;
    // не был выше платформы


    return does_player_overlap_platform (player, player_skin, platform, platform_skin);
}


bool does_player_overlap_platform
(Player player, Player_Skin player_skin, Platform platform, Platform_Skin platform_skin)
{

    for (size_t i = 0; i < player_skin.legs_hitbox.size; i++) {

        Hitbox_Rect true_player_rect =
            player_get_true_hitbox_rect (player, player_skin, i);


        if (does_hitbox_overlap_true_hitbox_rect
            (platform.motion, platform_skin.hitbox, true_player_rect)) return true;
    }


    return false;
}


static bool does_hitbox_overlap_true_hitbox_rect
(Object_Motion coords, Array hitbox, Hitbox_Rect true_rect)
{

    Hitbox_Rect cur_hitbox_rect      = {};
    Hitbox_Rect cur_hitbox_true_rect = {};


    for (size_t i = 0; i < hitbox.size; i++) {

        cur_hitbox_rect      = array_get_hitbox_rect (hitbox, i);
        cur_hitbox_true_rect = motion_get_true_hitbox_rect (coords, cur_hitbox_rect);


        if (do_hitbox_rects_overlap (true_rect, cur_hitbox_true_rect)) return true;
    }


    return false;
}



static bool do_hitbox_rects_overlap (Hitbox_Rect rect1, Hitbox_Rect rect2) {

    if (rect1.x + rect1.w < rect2.x) return false;
    if (rect2.x + rect2.w < rect1.x) return false;

    if (rect1.y < rect2.y - rect2.h) return false;
    if (rect2.y < rect1.y - rect1.h) return false;


    return true;
}


Return_code hitbox_rect_mirror_horizontally (Hitbox_Rect* rect) {

    if (!rect) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    rect->x += rect->w; // правый край переходит в левый


    rect->x *= -1;


    return SUCCESS;
}

