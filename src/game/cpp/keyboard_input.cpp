

//--------------------------------------------------


#include "../hpp/game.hpp"


//--------------------------------------------------


Return_code game_handle_keyboard_input (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (game->data.game_mode) {

        case SINGLE_PLAYER: game_handle_keyboard_input_singleplayer (game); break;
        case DUO:
        default:
    }


    return SUCCESS;
}


Return_code game_handle_keyboard_input_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Event event = {};


    while (SDL_PollEvent (&event)) {

        if (event.type == SDL_QUIT) {

            game->conditions.exit = true;
            break;
        }


        if (event.type == SDL_KEYDOWN) game_handle_keydown_singleplayer (game, event);
        if (event.type == SDL_KEYUP)   game_handle_keyup_singleplayer   (game, event);
    }


    return SUCCESS;
}


//--------------------------------------------------

Return_code game_handle_keydown_singleplayer (Game* game, SDL_Event event) {

    if (!game)                     { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (event.type != SDL_KEYDOWN) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (event.key.keysym.sym) {

        case SDLK_LEFT:  game_handle_left_down_singleplayer  (game); break;
        case SDLK_RIGHT: game_handle_right_down_singleplayer (game); break;
        case SDLK_a:     game_handle_a_down_singleplayer     (game); break;
        case SDLK_d:     game_handle_d_down_singleplayer     (game); break;


        default: break;
    }


    return SUCCESS;
}


Return_code game_handle_keyup_singleplayer (Game* game, SDL_Event event) {

    if (!game)                    { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (event.type != SDL_KEYUP) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (event.key.keysym.sym) {

        case SDLK_LEFT:  game_handle_left_up_singleplayer  (game); break;
        case SDLK_RIGHT: game_handle_right_up_singleplayer (game); break;
        case SDLK_a:     game_handle_a_up_singleplayer     (game); break;
        case SDLK_d:     game_handle_d_up_singleplayer     (game); break;

        default: break;
    }


    return SUCCESS;
}

//--------------------------------------------------

Return_code game_handle_left_down_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->conditions.pressed_left) return SUCCESS;
    game->conditions.pressed_left = true;


    game->field.players.buffer [0].motion.dx -= SMALL_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code game_handle_right_down_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->conditions.pressed_right) return SUCCESS;
    game->conditions.pressed_right = true;


    game->field.players.buffer [0].motion.dx += SMALL_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code game_handle_a_down_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->conditions.pressed_a) return SUCCESS;
    game->conditions.pressed_a = true;


    game->field.players.buffer [0].motion.dx -= BIG_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code game_handle_d_down_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->conditions.pressed_d) return SUCCESS;
    game->conditions.pressed_d = true;


    game->field.players.buffer [0].motion.dx += BIG_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code game_handle_left_up_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game->conditions.pressed_left = false;


    game->field.players.buffer [0].motion.dx += SMALL_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code game_handle_right_up_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game->conditions.pressed_right = false;


    game->field.players.buffer [0].motion.dx -= SMALL_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code game_handle_a_up_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game->conditions.pressed_a = false;


    game->field.players.buffer [0].motion.dx += BIG_HORIZONTAL_STEP;


    return SUCCESS;
}


Return_code game_handle_d_up_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game->conditions.pressed_d = false;


    game->field.players.buffer [0].motion.dx -= BIG_HORIZONTAL_STEP;


    return SUCCESS;
}

//--------------------------------------------------