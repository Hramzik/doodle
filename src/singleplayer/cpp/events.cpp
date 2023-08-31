

//--------------------------------------------------


#include "../hpp/singleplayer.hpp"
#include "../hpp/dsl.hpp"


//--------------------------------------------------


#define PLAYER list_get_player (game->engine.players.list, 0)


//--------------------------------------------------


Return_code player_teleport_mid (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    PLAYER->motion.x = game->engine.data.field_width / 2;
    PLAYER->motion.y = game->data.camera_y + game->engine.data.field_height * 0.4;
    PLAYER->max_cur_jump_y = PLAYER->motion.y;


    PLAYER->motion.dy = 0;


    return SUCCESS;
}


Return_code player_fly_up_launch (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    PLAYER->motion.dy  = 10;
    PLAYER->motion.ddy = 0;


    return SUCCESS;
}


Return_code player_fly_up_terminate (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    PLAYER->motion.dy  = DEFAULT_PLAYER_DY;
    PLAYER->motion.ddy = DEFAULT_PLAYER_DDY;


    return SUCCESS;
}


Return_code player_freeze_launch (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    PLAYER->vertically_frozen = true;


    return SUCCESS;
}


Return_code player_freeze_terminate (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    PLAYER->vertically_frozen = false;


    return SUCCESS;
}


Return_code player_switch_texture_direction (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (PLAYER->facing == PFD_LEFT)  PLAYER->facing = PFD_RIGHT;
    else                             PLAYER->facing = PFD_LEFT;


    return SUCCESS;
}


Return_code player_next_skin (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (PLAYER->skin == game->engine.players.skins.size - 1) return SUCCESS;


    PLAYER->skin += 1;


    return SUCCESS;
}


Return_code player_prev_skin (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (PLAYER->skin == 0) return SUCCESS;


    PLAYER->skin -= 1;


    return SUCCESS;
}

