

//--------------------------------------------------


#include "../hpp/engine.hpp"
#include "../hpp/dsl.hpp"


//--------------------------------------------------


static Return_code engine_move_platform      (Game_Engine* engine, Platform* platform);
static Return_code ensure_platform_on_screen (Game_Engine* engine, Platform* platform);

static Return_code update_cur_skin (Platforms_Data* data, Platform_type type, size_t skin);


//--------------------------------------------------


Return_code engine_move_platforms (Game_Engine* engine) {

    if (!engine) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < engine->platforms.list.len; i++) {

        engine_move_platform (engine, list_get_platform (engine->platforms.list, i));
    }


    return SUCCESS;
}


static Return_code engine_move_platform (Game_Engine* engine, Platform* platform) {

    if (!engine)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!platform) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    motion_update (&platform->motion, engine->data.t);


    return ensure_platform_on_screen (engine, platform);
}


static Return_code ensure_platform_on_screen (Game_Engine* engine, Platform* platform) {

    if (!engine)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!platform) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Platform_Skin skin = engine_get_platform_skin (*engine, *platform);

    double min_x = -skin.texture_offset.x;
    double max_x = ENGINE_FIELD_WIDTH - skin.texture_offset.x - skin.texture_offset.w;


    motion_ensure_x_ge_than (&platform->motion, min_x);
    motion_ensure_x_le_than (&platform->motion, max_x);


    return SUCCESS;
}


static size_t* data_get_platform_type_skin_index (Platforms_Data* data, Platform_type type) {

    if (!data) { LOG_ERROR (BAD_ARGS); return nullptr; }


    switch (type) {

        case PT_DEFAULT: return &data->cur_default_skin;
        case PT_MOVING:  return &data->cur_moving_skin;
        case PT_FAKE:    return &data->cur_fake_skin;
        case PT_CLOUD:   return &data->cur_cloud_skin;

        default: LOG_ERROR (CRITICAL); return nullptr;
    }
}


Platform_Skin engine_get_platform_skin (Game_Engine engine, Platform platform) {


    return engine_get_platform_type_skin (engine, platform.type);
}


Platform_Skin engine_get_platform_type_skin (Game_Engine engine, Platform_type type) {


    size_t skin_index = *data_get_platform_type_skin_index (&engine.platforms.data, type);


    return array_get_platform_skin (engine.platforms.skins, skin_index);
}


Return_code platforms_data_update_cur_skins (Platforms_Data* data, Array platform_types, size_t skin) {

    if (!data) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < platform_types.size; i++) {

        update_cur_skin (data, array_get_platform_type (platform_types, i), skin);
    }


    return SUCCESS;
}


static Return_code update_cur_skin (Platforms_Data* data, Platform_type type, size_t skin) {

    if (!data) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    *data_get_platform_type_skin_index (data, type) = skin;


    return SUCCESS;
}

