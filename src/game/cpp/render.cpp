


//--------------------------------------------------


#include "../hpp/game.hpp"


//--------------------------------------------------


static Hitbox_Rect get_player_cross_rect_x (void);
static Hitbox_Rect get_player_cross_rect_y (void);
static Return_code game_render_player_cross (Game* game, Player player);


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

    for (size_t i = 0; i < game->engine.players.list.len; i++) {

        game_render_player (game, *list_get_player (game->engine.players.list, i));
    }


    return SUCCESS;
}


Return_code game_render_platforms (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < game->engine.platforms.list.len; i++) {

        game_render_platform (game, *list_get_platform (game->engine.platforms.list, i));
    }


    return SUCCESS;
}


Return_code game_render_player (Game* game, Player player) {

    if (!game)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Player_Skin skin = engine_get_player_skin (game->engine, player);


    SDL_Rect texture_offset = skin.texture_offset;
    SDL_Rect dstrect = game_get_render_rect (game, player.motion, texture_offset);


    SDL_RendererFlip flip = player_get_sdl_flip (player, skin);
    SDL_RenderCopyEx (game->output.renderer, skin.texture, nullptr, &dstrect, 0, nullptr, flip);


    if (RENDER_HITBOXES) game_render_player_hitboxes (game, player);
    if (RENDER_CROSSES)  game_render_player_cross    (game, player);


    return SUCCESS;
}


Return_code game_render_player_hitboxes (Game* game, Player player) {

    if (!game)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Player_Skin skin = array_get_player_skin (game->engine.players.skins, player.skin);
    bool flip_hitbox = (player.facing != skin.default_face_direction);


    game_set_drawcolor      (game, 0, 0, 255);
    game_draw_object_hitbox (game, player.motion, skin.legs_hitbox, flip_hitbox);

    game_set_drawcolor      (game, 3, 150, 96);
    game_draw_object_hitbox (game, player.motion, skin.good_hitbox, flip_hitbox);


    return SUCCESS;
}


static Return_code game_render_player_cross (Game* game, Player player) {

    if (!game)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Hitbox_Rect cross_rect_x = get_player_cross_rect_x ();
    Hitbox_Rect cross_rect_y = get_player_cross_rect_y ();


    game_set_drawcolor           (game, 150, 20, 20);
    game_draw_object_hitbox_rect (game, player.motion, cross_rect_x);
    game_draw_object_hitbox_rect (game, player.motion, cross_rect_y);


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
    SDL_Rect render_rect    = game_get_render_rect   (game, coords, texture_offset);


    game_draw_rect (game, render_rect);


    return SUCCESS;
}


SDL_RendererFlip player_get_sdl_flip (Player player, Player_Skin skin) {

    if (player.facing != skin.default_face_direction) return SDL_FLIP_HORIZONTAL;


    return SDL_FLIP_NONE;
}


Return_code game_render_platform (Game* game, Platform platform) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Platform_Skin skin = engine_get_platform_skin (game->engine, platform);


    SDL_Rect texture_offset = skin.texture_offset;
    SDL_Rect dstrect = game_get_render_rect (game, platform.motion, texture_offset);


    SDL_RenderCopy (game->output.renderer, skin.texture, nullptr, &dstrect);


    if (RENDER_HITBOXES) game_render_platform_hitbox (game, platform);


    return SUCCESS;
}


Return_code game_render_platform_hitbox (Game* game, Platform platform) {

    if (!game)     { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Platform_Skin skin = engine_get_platform_skin (game->engine, platform);


    game_set_drawcolor      (game, 0, 0, 255);
    game_draw_object_hitbox (game, platform.motion, skin.hitbox);


    return SUCCESS;
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


SDL_Rect game_get_render_rect (Game* game, Object_Motion motion, SDL_Rect texture_offset) {

    SDL_Rect rect;

    rect.x =   texture_offset.x + (int) (motion.x);
    rect.y = - texture_offset.y + (GAME_WINDOW_HEIGHT) - (int) (motion.y - game->data.camera_y);

    // нормировка из-за разных размеров поля и окна
    rect.x += (GAME_WINDOW_WIDTH - GAME_FIELD_WIDTH_INT) / 2;
    rect.y += 0; // рисуется все с самого низу


    rect.w = texture_offset.w;
    rect.h = texture_offset.h;


    return rect;
}


SDL_Rect hitbox_rect_to_sdl_rect (Hitbox_Rect hitbox) {

    SDL_Rect rect;


    rect.x = (int) hitbox.x;
    rect.y = (int) hitbox.y;

    rect.w = (int) hitbox.w;
    rect.h = (int) hitbox.h;


    return rect;
}


static Hitbox_Rect get_player_cross_rect_x (void) {

    Hitbox_Rect rect = {};


    rect.x = -20;
    rect.y =   0;
    rect.w =  40;
    rect.h =   1;


    return rect;
}


static Hitbox_Rect get_player_cross_rect_y (void) {

    Hitbox_Rect rect = {};


    rect.x =  0;
    rect.y = 40;
    rect.w =  1;
    rect.h = 40;


    return rect;
}

