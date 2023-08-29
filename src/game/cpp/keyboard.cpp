

//--------------------------------------------------

#include "../hpp/game.hpp"

//--------------------------------------------------


static void bool_reverse (bool* value) {

    if (*value) *value = false;
    else        *value = true;


    return;
}


static void game_background_reverse (Game_background* value) {

    if (*value == GB_FIELD) *value = GB_TRUE;
    else                    *value = GB_FIELD;


    return;
}


Return_code game_handle_keyboard_input (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (game->data.game_mode) {

        case SINGLE_PLAYER: game_handle_keyboard_input_singleplayer (game); break;
        case DUO:
        default: break;
    }


    return SUCCESS;
}


Return_code game_handle_keyboard_input_general (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_handle_keyboard_input_general_keydown (game);
    game_handle_keyboard_input_general_keyup   (game);


    return SUCCESS;
}


Return_code game_handle_keyboard_input_general_keydown (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_handle_keyboard_input_general_keydown (game);
    game_handle_keyboard_input_general_keyup   (game);


    return SUCCESS;
}


Return_code game_handle_keyboard_input_general_keyup (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_handle_keyboard_input_general_keydown (game);
    game_handle_keyboard_input_general_keyup   (game);


    return SUCCESS;
}


static size_t* game_get_changing_background (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return nullptr; }


    if (game->conditions.switching_background == GB_FIELD) return &game->data.background;


    return &game->data.true_background;
}


Return_code game_next_background (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    size_t* background = game_get_changing_background (game);


    if (*background == 0) return SUCCESS;


    *background -= 1;


    return SUCCESS;
}


Return_code game_prev_background (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    size_t* background = game_get_changing_background (game);


    if (*background == game->media.background_textures.size - 1) return SUCCESS;


    *background += 1;


    return SUCCESS;
}


Return_code game_toggle_fullscreen (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->conditions.fullscreen) SDL_SetWindowFullscreen (game->output.window, SDL_WINDOW_FULLSCREEN);
    else                             SDL_SetWindowFullscreen (game->output.window, 0);


    bool_reverse (&game->conditions.fullscreen);



    return SUCCESS;
}


Return_code game_toggle_render_hitboxes (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    bool_reverse (&game->conditions.render_hitboxes);


    return SUCCESS;
}


Return_code game_toggle_switching_background (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    background_reverse (&game->conditions.switching_background);


    return SUCCESS;
}

