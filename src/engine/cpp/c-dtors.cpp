

//--------------------------------------------------


#include "../hpp/engine.hpp"


//--------------------------------------------------


static Return_code engine_data_ctor    (Engine_Data* data);
static Return_code platforms_data_ctor (Platforms_Data* data);


//--------------------------------------------------


Return_code players_ctor (Players* players) {

    if (!players) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_ctor  (&players->list, LET_PLAYER);
    array_ctor (&players->skins,       AET_PLAYER_SKIN);


    return SUCCESS;
}


Return_code players_dtor (Players* players) {

    if (!players) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_dtor (&players->list);


    for (size_t i = 0; i < players->skins.size; i++) {

        SDL_DestroyTexture (array_get_player_skin (players->skins, i).texture);
    }

    array_dtor (&players->skins);


    return SUCCESS;
}


static Return_code platforms_data_ctor (Platforms_Data* data) {

    if (!data) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    data->max_y = 0;
    data->min_y = 0;
    data->max_material_y = 0;


    data->cur_default_skin = 0;
    data->cur_moving_skin  = 0;
    data->cur_fake_skin    = 0;
    data->cur_cloud_skin   = 0;


    return SUCCESS;
}


Return_code platforms_ctor (Platforms* platforms) {

    if (!platforms) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    array_ctor          (&platforms->skins, AET_PLATFORM_SKIN);
    list_ctor           (&platforms->list,  LET_PLATFORM);
    platforms_data_ctor (&platforms->data);


    return SUCCESS;
}


Return_code platforms_dtor (Platforms* platforms) {

    if (!platforms) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_dtor  (&platforms->list);
    array_dtor (&platforms->skins);


    return SUCCESS;
}


static Return_code engine_data_ctor (Engine_Data* data) {

    if (!data) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    data->t = DEFAULT_UPDATE_TIME;

    data->field_width  = DEFAULT_FIELD_WIDTH;
    data->field_height = DEFAULT_FIELD_HEIGHT;


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

