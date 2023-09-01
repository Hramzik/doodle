

//--------------------------------------------------

#include "../hpp/game.hpp"

//--------------------------------------------------


static Return_code handle_keydown (Game* game, SDL_KeyboardEvent event);
static Return_code handle_keyup   (Game* game, SDL_KeyboardEvent event);
static Return_code next_background             (Game* game);
static Return_code prev_background             (Game* game);
static Return_code toggle_fullscreen           (Game* game);
static Return_code toggle_render_hitboxes      (Game* game);
static Return_code toggle_render_crosses       (Game* game);
static Return_code toggle_switching_background (Game* game);
static size_t*     get_changing_background     (Game* game);


//--------------------------------------------------


static void bool_reverse (bool* value) {

    if (*value) *value = false;
    else        *value = true;


    return;
}


static void background_reverse (Game_background* value) {

    if (*value == GB_FIELD) *value = GB_TRUE;
    else                    *value = GB_FIELD;


    return;
}


//--------------------------------------------------


Return_code game_handle_keyboard_input (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Event event = {};


    while (SDL_PollEvent (&event)) {

        if (event.type == SDL_QUIT) {

            game->conditions.exit = true;
            break;
        }


        if (event.type == SDL_KEYDOWN) handle_keydown (game, event.key);
        if (event.type == SDL_KEYUP)   handle_keyup   (game, event.key);
    }


    return SUCCESS;
}


static Return_code handle_keydown (Game* game, SDL_KeyboardEvent event) {

    if (!game)                     { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (event.type != SDL_KEYDOWN) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (event.keysym.sym) {

        default: game_handle_keydown_singleplayer (game, event);
    }


    return SUCCESS;
}


static Return_code handle_keyup (Game* game, SDL_KeyboardEvent event) {

    if (!game)                   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (event.type != SDL_KEYUP) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (event.keysym.sym) {

        case SDLK_COMMA:  prev_background             (game); break;
        case SDLK_PERIOD: next_background             (game); break;
        case SDLK_h:      toggle_render_hitboxes      (game); break;
        case SDLK_c:      toggle_render_crosses       (game); break;
        case SDLK_b:      toggle_switching_background (game); break;
        case SDLK_F11:    toggle_fullscreen           (game); break;


        default: game_handle_keyup_singleplayer (game, event);
    }


    return SUCCESS;
}


static size_t* get_changing_background (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return nullptr; }


    if (game->conditions.switching_background == GB_FIELD) return &game->data.background;


    return &game->data.true_background;
}


static Return_code next_background (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    size_t* background = get_changing_background (game);


    if (*background == game->media.background_textures.size - 1) return SUCCESS;


    *background += 1;


    return SUCCESS;
}


static Return_code prev_background (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    size_t* background = get_changing_background (game);


    if (*background == 0) return SUCCESS;


    *background -= 1;


    return SUCCESS;
}


static Return_code toggle_fullscreen (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->conditions.fullscreen) SDL_SetWindowFullscreen (game->output.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    else                             SDL_SetWindowFullscreen (game->output.window, 0);


    bool_reverse (&game->conditions.fullscreen);



    return SUCCESS;
}


static Return_code toggle_render_hitboxes (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    bool_reverse (&game->conditions.render_hitboxes);


    return SUCCESS;
}


static Return_code toggle_render_crosses (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    bool_reverse (&game->conditions.render_crosses);


    return SUCCESS;
}


static Return_code toggle_switching_background (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    background_reverse (&game->conditions.switching_background);


    return SUCCESS;
}

