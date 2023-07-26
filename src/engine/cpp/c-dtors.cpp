

//--------------------------------------------------

#include "../hpp/engine.hpp"

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


    platforms->list = list_ctor (LET_PLATFORM);


    platforms->count = 0;
    platforms->max_y = 0;
    platforms->min_y = 0;


    return SUCCESS;
}


Return_code platforms_dtor (Platforms* platforms) {

    if (!platforms) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_dtor (platforms->list);


    return SUCCESS;
}


Return_code engine_data_ctor (Engine_Data* data) {

    if (!data) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    data->t = DEFAULT_UPDATE_TIME;


    return SUCCESS;
}


Return_code game_engine_ctor (Game_Engine* engine) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    players_ctor     (&engine->players);
    platforms_ctor   (&engine->platforms);
    engine_data_ctor (&engine->data);


    return SUCCESS;
}


Return_code game_engine_dtor (Game_Engine* engine) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    players_dtor   (&engine->players);
    platforms_dtor (&engine->platforms);


    return SUCCESS;
}

