

//--------------------------------------------------

#include "../hpp/field.hpp"

//--------------------------------------------------


Return_code players_ctor (Players* players) {

    if (!players) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    players->buffer  = (Player*) calloc (MAX_PLAYERS_COUNT, PLAYER_SIZE);


    players->count = 0;


    return SUCCESS;
}


Return_code players_dtor (Players* players) {

    if (!players) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    free (players->buffer);


    return SUCCESS;
}


Return_code platforms_ctor (Platforms* platforms) {

    if (!platforms) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    platforms->buffer  = (Platform*) calloc (MAX_PLATFORMS_COUNT, PLATFORM_SIZE);


    platforms->count = 0;
    platforms->max_y = 0;
    platforms->min_y = 0;


    return SUCCESS;
}


Return_code platforms_dtor (Platforms* platforms) {

    if (!platforms) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    free (platforms->buffer);


    return SUCCESS;
}


Return_code game_field_ctor (Game_Field* field) {

    if (!field) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    players_ctor   (&field->players);
    platforms_ctor (&field->platforms);


    return SUCCESS;
}


Return_code game_field_dtor (Game_Field* field) {

    if (!field) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    players_dtor   (&field->players);
    platforms_dtor (&field->platforms);


    return SUCCESS;
}

