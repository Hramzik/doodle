

//--------------------------------------------------

#include "../hpp/singleplayer.hpp"
#include "../hpp/dsl.hpp"

//--------------------------------------------------


Return_code player_teleport_mid (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_get_player (game->engine.players.player_list, 0)->motion.x = game->engine.data.field_width / 2;
    list_get_player (game->engine.players.player_list, 0)->motion.y = game->data.camera_y + game->engine.data.field_height * 0.4;

    list_get_player (game->engine.players.player_list, 0)->motion.dy = 0;


    return SUCCESS;
}


Return_code player_fly_up_launch (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_get_player (game->engine.players.player_list, 0)->motion.dy  = 10;
    list_get_player (game->engine.players.player_list, 0)->motion.ddy = 0;


    return SUCCESS;
}


Return_code player_fly_up_terminate (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_get_player (game->engine.players.player_list, 0)->motion.dy  = DEFAULT_PLAYER_DY;
    list_get_player (game->engine.players.player_list, 0)->motion.ddy = DEFAULT_PLAYER_DDY;


    return SUCCESS;
}


Return_code player_freeze_launch (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_get_player (game->engine.players.player_list, 0)->vertically_frozen = true;


    return SUCCESS;
}


Return_code player_freeze_terminate (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_get_player (game->engine.players.player_list, 0)->vertically_frozen = false;


    return SUCCESS;
}


Return_code player_switch_texture_direction (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (PLAYER->facing == PFD_LEFT)  PLAYER->facing = PFD_RIGHT;
    else                             PLAYER->facing = PFD_LEFT;


    return SUCCESS;
}

