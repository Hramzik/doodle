

//--------------------------------------------------

#include "../hpp/singleplayer.hpp"

//--------------------------------------------------


Return_code game_handle_keyboard_input_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Event event = {};


    while (SDL_PollEvent (&event)) {

        if (event.type == SDL_QUIT) {

            game->conditions.exit = true;
            break;
        }


        if (event.type == SDL_KEYDOWN) game_handle_keydown (game, event);
        if (event.type == SDL_KEYUP)   game_handle_keyup   (game, event);
    }


    return SUCCESS;
}


//--------------------------------------------------

Return_code handle_keydown (Game* game, SDL_Event event) {

    if (!game)                     { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (event.type != SDL_KEYDOWN) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (event.key.keysym.sym) {

        case SDLK_LEFT:  handle_left_down  (game); break;
        case SDLK_RIGHT: handle_right_down (game); break;
        case SDLK_a:     handle_a_down     (game); break;
        case SDLK_d:     handle_d_down     (game); break;
        case SDLK_KP_8:  player_fly_up_launch     (game); break;
        case SDLK_KP_5:  player_freeze_launch     (game); break;


        default: break;
    }


    return SUCCESS;
}


Return_code handle_keyup (Game* game, SDL_Event event) {

    if (!game)                    { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (event.type != SDL_KEYUP) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (event.key.keysym.sym) {

        case SDLK_LEFT:  handle_left_up   (game); break;
        case SDLK_RIGHT: handle_right_up  (game); break;
        case SDLK_a:     handle_a_up      (game); break;
        case SDLK_d:     handle_d_up      (game); break;
        case SDLK_KP_0:  player_teleport_mid     (game); break;
        case SDLK_KP_8:  player_fly_up_terminate (game); break;
        case SDLK_KP_5:  player_freeze_terminate (game); break;
        case SDLK_KP_MULTIPLY: player_switch_texture_direction (game); break;

        case SDLK_COMMA:  handle_comma_up    (game); break;
        case SDLK_PERIOD: handle_period_up (game); break;

        case SDLK_h: game_toggle_render_hitboxes      (game); break;
        case SDLK_b: game_toggle_switching_background (game); break;

        case SDLK_F11: toggle_fullscreen (game); break;

        default: break;
    }


    return SUCCESS;
}

//--------------------------------------------------

Return_code handle_left_down (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->conditions.pressed_left) return SUCCESS;
    game->conditions.pressed_left = true;


    list_get_player (game->engine.players.player_list, 0)->motion.dx -= SMALL_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code handle_right_down (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->conditions.pressed_right) return SUCCESS;
    game->conditions.pressed_right = true;


    list_get_player (game->engine.players.player_list, 0)->motion.dx += SMALL_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code handle_a_down (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->conditions.pressed_a) return SUCCESS;
    game->conditions.pressed_a = true;


    list_get_player (game->engine.players.player_list, 0)->motion.dx -= BIG_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code handle_d_down (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->conditions.pressed_d) return SUCCESS;
    game->conditions.pressed_d = true;


    list_get_player (game->engine.players.player_list, 0)->motion.dx += BIG_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code handle_left_up (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game->conditions.pressed_left = false;


    list_get_player (game->engine.players.player_list, 0)->motion.dx += SMALL_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code handle_right_up (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game->conditions.pressed_right = false;


    list_get_player (game->engine.players.player_list, 0)->motion.dx -= SMALL_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code handle_a_up (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game->conditions.pressed_a = false;


    list_get_player (game->engine.players.player_list, 0)->motion.dx += BIG_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code handle_d_up (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game->conditions.pressed_d = false;


    list_get_player (game->engine.players.player_list, 0)->motion.dx -= BIG_HORIZONTAL_STEP;


    return SUCCESS;
}

