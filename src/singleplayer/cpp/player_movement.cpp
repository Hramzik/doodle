

//--------------------------------------------------

#include "../hpp/singleplayer.hpp"
#include "../hpp/dsl.hpp"

//--------------------------------------------------


Return_code game_teleport_mid_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_get_player (game->engine.players.list, 0)->motion.x = game->engine.data.field_width / 2;
    list_get_player (game->engine.players.list, 0)->motion.y = game->data.camera_y + game->engine.data.field_height * 0.4;

    list_get_player (game->engine.players.list, 0)->motion.dy = 0;


    return SUCCESS;
}


Return_code game_fly_up_singleplayer_launch (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_get_player (game->engine.players.list, 0)->motion.dy  = 10;
    list_get_player (game->engine.players.list, 0)->motion.ddy = 0;


    return SUCCESS;
}


Return_code game_fly_up_singleplayer_terminate (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_get_player (game->engine.players.list, 0)->motion.dy  = DEFAULT_PLAYER_DY;
    list_get_player (game->engine.players.list, 0)->motion.ddy = DEFAULT_PLAYER_DDY;


    return SUCCESS;
}


Return_code game_freeze_singleplayer_launch (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_get_player (game->engine.players.list, 0)->motion.dy  = 0;
    list_get_player (game->engine.players.list, 0)->motion.ddy = 0;


    return SUCCESS;
}


Return_code game_freeze_singleplayer_terminate (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_get_player (game->engine.players.list, 0)->motion.dy  = 0;
    list_get_player (game->engine.players.list, 0)->motion.ddy = DEFAULT_PLAYER_DDY;


    return SUCCESS;
}


Return_code game_switch_player_texture_direction_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (PLAYER->facing == PFD_LEFT)  PLAYER->facing = PFD_RIGHT;
    else                             PLAYER->facing = PFD_LEFT;


    return SUCCESS;
}

