


//--------------------------------------------------


#include "../hpp/game.hpp"


//--------------------------------------------------


static SDL_Texture* game_get_background_texture      (Game* game);
static SDL_Texture* game_get_true_background_texture (Game* game);


static SDL_Rect game_get_background_texture_offset      (Game* game);
static SDL_Rect game_get_true_background_texture_offset (Game* game);


//--------------------------------------------------


static SDL_Point texture_get_size (SDL_Texture* texture) {

    if (!texture) { LOG_ERROR (BAD_ARGS); return {}; }


    SDL_Point size;
    SDL_QueryTexture (texture, nullptr, nullptr, &size.x, &size.y);


    return size;
}


// offset from down-centered point in normal coords (right +x, top +y)
static SDL_Rect texture_get_srcrect
(SDL_Texture* texture, int dstwidth, int dstheight, SDL_Point offset = { 0, 0 }) {

    if (!texture) { LOG_ERROR (BAD_ARGS); return {}; }


    SDL_Point texture_size = texture_get_size (texture);


    SDL_Rect srcrect;

    srcrect.x = texture_size.x / 2 - dstwidth / 2;
    srcrect.y = texture_size.y     - dstheight;

    srcrect.x += offset.x;
    srcrect.y -= offset.y;


    srcrect.w = dstwidth;
    srcrect.h = dstheight;


    return srcrect;
}


Return_code game_render_background (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* texture = game_get_background_texture (game);


    SDL_Rect srcrect = texture_get_srcrect (texture, GAME_FIELD_WIDTH_INT, GAME_FIELD_HEIGHT_INT);

    Object_Motion motion         = game_get_background_motion (game);
    SDL_Rect      texture_offset = game_get_background_texture_offset (game);
    SDL_Rect      dstrect        = game_get_render_rect (game, motion, texture_offset);


    SDL_RenderCopy (game->output.renderer, texture, &srcrect, &dstrect);


    return SUCCESS;
}


Return_code game_render_true_background (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* texture = game_get_true_background_texture (game);


    SDL_Rect srcrect = texture_get_srcrect (texture, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);

    Object_Motion motion    = game_get_true_background_motion (game);
    SDL_Rect texture_offset = game_get_true_background_texture_offset (game);
    SDL_Rect dstrect = game_get_render_rect (game, motion, texture_offset);


    SDL_RenderCopy (game->output.renderer, texture, &srcrect, &dstrect);


    return SUCCESS;
}


static SDL_Texture* game_get_background_texture (Game* game) {

    if (!game)     { LOG_ERROR (BAD_ARGS); return nullptr; }


    return array_get_texture (game->media.background_textures, game->data.background);
}


static SDL_Texture* game_get_true_background_texture (Game* game) {

    if (!game)     { LOG_ERROR (BAD_ARGS); return nullptr; }


    return array_get_texture (game->media.background_textures, game->data.true_background);
}


static SDL_Rect game_get_background_texture_offset (Game* game) {

    SDL_Rect offset;


    offset.x = - GAME_FIELD_WIDTH_INT / 2;
    offset.y =   GAME_FIELD_HEIGHT_INT;
    offset.w =   GAME_FIELD_WIDTH_INT;
    offset.h =   GAME_FIELD_HEIGHT_INT;


    return offset;
}


static SDL_Rect game_get_true_background_texture_offset (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return {}; }


    SDL_Rect offset;


    offset.x = - GAME_WINDOW_WIDTH / 2;
    offset.y =   GAME_WINDOW_HEIGHT;
    offset.w =   GAME_WINDOW_WIDTH;
    offset.h =   GAME_WINDOW_HEIGHT;


    return offset;
}


Object_Motion game_get_background_motion (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return {}; }


    return static_motion (game->engine.data.field_width / 2, game->data.camera_y);
}


Object_Motion game_get_true_background_motion (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return {}; }


    return game_get_background_motion (game);
}

