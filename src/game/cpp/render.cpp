


//--------------------------------------------------

#include "../hpp/game.hpp"

//--------------------------------------------------


Return_code game_clear_screen (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_set_drawcolor (game, 0, 0, 0);
    SDL_RenderClear    (game->output.renderer);


    return SUCCESS;
}


Return_code game_set_drawcolor (Game* game, Uint8 r, Uint8 g, Uint8 b) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_SetRenderDrawColor (game->output.renderer, r, g, b, 0);


    return SUCCESS;
}


Return_code game_draw_rect (Game* game, SDL_Rect rect) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_RenderDrawRect (game->output.renderer, &rect);


    return SUCCESS;
}


Return_code game_render (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_render_true_background (game);
    game_render_background      (game);
    game_render_platforms       (game);
    game_render_players         (game);


    return SUCCESS;
}


Return_code game_render_players (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }

    for (size_t i = 0; i < game->engine.players.player_list.len; i++) {

        game_render_player (game, list_get_player (game->engine.players.player_list, i));
    }


    return SUCCESS;
}


Return_code game_render_platforms (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < game->engine.platforms.list.len; i++) {

        game_render_platform (game, list_get_platform (game->engine.platforms.list, i));
    }


    return SUCCESS;
}


Return_code game_render_player (Game* game, Player* player) {

    if (!game)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* player_texture = array_get_player_skin (game->engine.players.skins, player->skin).texture;


    SDL_Rect texture_offset = game_get_player_texture_offset (game, player);
    SDL_Rect dstrect = game_get_render_rect (game, &player->motion, texture_offset);


    SDL_RendererFlip flip = player_get_sdl_flip (player);
    SDL_RenderCopyEx (game->output.renderer, player_texture, nullptr, &dstrect, 0, nullptr, flip);


    if (RENDER_HITBOXES) game_render_player_hitboxes (game, player);


    return SUCCESS;
}


Return_code game_render_player_hitboxes (Game* game, Player* player) {

    if (!game)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Player_Skin skin = array_get_player_skin (game->engine.players.skins, player->skin);
    bool flip_hitbox = (player->facing != skin.default_face_direction);


    game_set_drawcolor      (game, 0, 0, 255);
    game_draw_object_hitbox (game, player->motion, skin.legs_hitbox, flip_hitbox);

    game_set_drawcolor      (game, 3, 150, 96);
    game_draw_object_hitbox (game, player->motion, skin.good_hitbox, flip_hitbox);


    return SUCCESS;
}


Return_code game_draw_object_hitbox
(Game* game, Object_Motion coords, Array hitbox, bool flip_horizontally)
{

    if (!game)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < hitbox.size; i++) {

        Hitbox_Rect rect = array_get_hitbox_rect (hitbox, i);
        if (flip_horizontally) hitbox_rect_mirror_horizontally (&rect);


        game_draw_object_hitbox_rect (game, coords, rect);
    }


    return SUCCESS;
}


Return_code game_draw_object_hitbox_rect
(Game* game, Object_Motion coords, Hitbox_Rect hitbox_rect)
{

    if (!game)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Rect texture_offset = hitbox_rect_to_sdl_rect (hitbox_rect);
    SDL_Rect render_rect    = game_get_render_rect   (game, &coords, texture_offset);


    game_draw_rect (game, render_rect);


    return SUCCESS;
}


SDL_RendererFlip player_get_sdl_flip (Player* player) {

    if (!player) { LOG_ERROR (BAD_ARGS); return SDL_FLIP_NONE; }


    if (player->facing == PFD_LEFT) return SDL_FLIP_HORIZONTAL;


    return SDL_FLIP_NONE;
}


Return_code game_render_platform (Game* game, Platform* platform) {

    if (!game)     { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!platform) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* platform_texture = game_get_platform_texture (game, platform);


    SDL_Rect texture_offset = get_platform_texture_offset ();
    SDL_Rect dstrect = game_get_render_rect (game, &platform->motion, texture_offset);


    SDL_RenderCopy (game->output.renderer, platform_texture, nullptr, &dstrect);


    if (RENDER_HITBOXES) game_render_platform_hitbox (game, platform);


    return SUCCESS;
}


Return_code game_render_platform_hitbox (Game* game, Platform* platform) {

    if (!game)     { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!platform) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_set_drawcolor (game, 0, 0, 255);

    Hitbox_Rect hitbox_rect = get_platform_hitbox_rect ();
    game_draw_object_hitbox_rect (game, platform->motion, hitbox_rect);


    return SUCCESS;
}


// переписать ьв новом стиле!
Return_code game_render_background (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* background_texture = game_get_background_texture (game);


    SDL_Rect srcrect;
    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = GAME_FIELD_WIDTH_INT;
    srcrect.h = GAME_FIELD_HEIGHT_INT;


    Object_Motion motion    = game_get_background_motion (game);
    SDL_Rect texture_offset = game_get_background_texture_offset (game);
    SDL_Rect dstrect = game_get_render_rect (game, &motion, texture_offset);


    SDL_RenderCopy (game->output.renderer, background_texture, &srcrect, &dstrect);


    return SUCCESS;
}


Return_code game_render_true_background (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* background_texture = game_get_true_background_texture (game);


    SDL_Rect srcrect;
    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = GAME_WINDOW_WIDTH;
    srcrect.h = GAME_WINDOW_HEIGHT;


    Object_Motion motion    = game_get_true_background_motion (game);
    SDL_Rect texture_offset = game_get_true_background_texture_offset (game);
    SDL_Rect dstrect = game_get_render_rect (game, &motion, texture_offset);


    SDL_RenderCopy (game->output.renderer, background_texture, &srcrect, &dstrect);


    return SUCCESS;
}


SDL_Texture* game_get_platform_texture (Game* game, Platform* platform) {

    if (!game)     { LOG_ERROR (BAD_ARGS); return nullptr; }
    if (!platform) { LOG_ERROR (BAD_ARGS); return nullptr; }


    switch (platform->type) {

        case PT_DEFAULT: return array_get_texture (game->media.platform_textures, 0);
        case PT_FAKE:    return array_get_texture (game->media.platform_textures, 1);
        case PT_MOVING:  return array_get_texture (game->media.platform_textures, 0);
        case PT_CLOUD:   return array_get_texture (game->media.platform_textures, 2);

        default: LOG_ERROR (CRITICAL); return nullptr;
    }
}


SDL_Texture* game_get_background_texture (Game* game) {

    if (!game)     { LOG_ERROR (BAD_ARGS); return nullptr; }


    return array_get_texture (game->media.background_textures, game->data.background);
}


SDL_Texture* game_get_true_background_texture (Game* game) {

    if (!game)     { LOG_ERROR (BAD_ARGS); return nullptr; }


    return array_get_texture (game->media.background_textures, game->data.true_background);
}


int game_get_window_width (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    int width = 0;
    SDL_GetWindowSize (game->output.window, &width, nullptr);


    return width;
}


int game_get_window_height (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    int height = 0;
    SDL_GetWindowSize (game->output.window, nullptr, &height);


    return height;
}


SDL_Rect game_get_render_rect (Game* game, Object_Motion* motion, SDL_Rect texture_offset) {

    SDL_Rect rect;

    rect.x =   texture_offset.x + (int) (motion->x);
    rect.y = - texture_offset.y + (GAME_WINDOW_HEIGHT) - (int) (motion->y - game->data.camera_y);

    // нормировка из-за разных размеров поля и окна
    rect.x += (GAME_WINDOW_WIDTH - GAME_FIELD_WIDTH_INT) / 2;
    rect.y += 0; // рисуется все с самого низу


    rect.w = texture_offset.w;
    rect.h = texture_offset.h;


    return rect;
}


// offset is defined using normal coordinates! (+x left, +y up)

SDL_Rect get_platform_texture_offset (void) {

    SDL_Rect rect;


    rect.x = - PLATFORM_TEXTURE_WIDTH / 2;
    rect.y =   PLATFORM_TEXTURE_HEIGHT;

    rect.w = PLATFORM_TEXTURE_WIDTH;
    rect.h = PLATFORM_TEXTURE_HEIGHT;


    return rect;
}


SDL_Rect game_get_player_texture_offset (Game* game, Player* player) {

    if (!player) { LOG_ERROR (BAD_ARGS); return {}; }


    return array_get_player_skin (game->engine.players.skins, player->skin).texture_offset;
}


SDL_Rect hitbox_rect_to_sdl_rect (Hitbox_Rect hitbox) {

    SDL_Rect rect;


    rect.x = (int) hitbox.x;
    rect.y = (int) hitbox.y;

    rect.w = (int) hitbox.w;
    rect.h = (int) hitbox.h;


    return rect;
}


SDL_Rect get_platform_hitbox_offset (void) {

    SDL_Rect rect;


    rect.x = - (int) PLATFORM_HITBOX_WIDTH / 2;
    rect.y =         PLATFORM_HITBOX_HEIGHT;

    rect.w = PLATFORM_HITBOX_WIDTH;
    rect.h = PLATFORM_HITBOX_HEIGHT;


    return rect;
}


SDL_Rect game_get_background_texture_offset (Game* game) {

    SDL_Rect rect;


    rect.x = - GAME_FIELD_WIDTH_INT / 2;
    rect.y =   GAME_FIELD_HEIGHT_INT;
    rect.w =   GAME_FIELD_WIDTH_INT;
    rect.h =   GAME_FIELD_HEIGHT_INT;


    return rect;
}


SDL_Rect game_get_true_background_texture_offset (Game* game) {

    SDL_Rect rect;


    rect.x = - GAME_WINDOW_WIDTH / 2;
    rect.y =   GAME_WINDOW_HEIGHT;
    rect.w =   GAME_WINDOW_WIDTH;
    rect.h =   GAME_WINDOW_HEIGHT;


    return rect;
}


Object_Motion game_get_background_motion (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return {}; }


    return static_motion (game->engine.data.field_width / 2, game->data.camera_y);
}


Object_Motion game_get_true_background_motion (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return {}; }


    return game_get_background_motion (game);
}

