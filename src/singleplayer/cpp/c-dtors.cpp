

//--------------------------------------------------

#include "../hpp/singleplayer.hpp"

//--------------------------------------------------


#define INIT_DIFFICULTY(n) \
    data->num_difficulties += 1; \
    data->difficulties [n].max_score               = DIFFICULTY_##n##_MAX_SCORE; \
    data->difficulties [n].min_platform_gap        = DIFFICULTY_##n##_MIN_PLATFORM_GAP; \
    data->difficulties [n].max_platform_gap        = DIFFICULTY_##n##_MAX_PLATFORM_GAP; \
    data->difficulties [n].default_platform_chance = DIFFICULTY_##n##_DEFAULT_PLATFORM_CHANCE; \
    data->difficulties [n].   fake_platform_chance = DIFFICULTY_##n##_FAKE_PLATFORM_CHANCE; \
    data->difficulties [n]. moving_platform_chance = DIFFICULTY_##n##_MOVING_PLATFORM_CHANCE; \
    data->difficulties [n].  cloud_platform_chance = DIFFICULTY_##n##_CLOUD_PLATFORM_CHANCE; \
    data->difficulties [n].max_moving_platform_dx  = DIFFICULTY_##n##_MAX_MOVING_PLATFORM_DX; \
    data->difficulties [n].min_moving_platform_dx  = DIFFICULTY_##n##_MIN_MOVING_PLATFORM_DX; \

Return_code singleplayer_data_ctor (Singleplayer_Data* data) {

    if (!data) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    data->difficulties = (Difficulty*) calloc (NUM_DIFFICULTIES, DIFFICULTY_SIZE);
    data->num_difficulties = 0;


    INIT_DIFFICULTY (0);
    INIT_DIFFICULTY (1);
    INIT_DIFFICULTY (2);
    INIT_DIFFICULTY (3);
    INIT_DIFFICULTY (4);
    INIT_DIFFICULTY (5);


    return SUCCESS;
}

#undef INIT_DIFFICULTY
//--------------------------------------------------

