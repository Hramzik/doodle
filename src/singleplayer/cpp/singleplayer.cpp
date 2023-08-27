

//--------------------------------------------------

#include "../hpp/singleplayer.hpp"

//--------------------------------------------------


Return_code game_spawn_players_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->engine.players.player_list.len >= 1) return SUCCESS;


    Player player = generate_default_player (game);
    game_add_player (game, player);


    return SUCCESS;
}


Player generate_default_player (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); }


    Object_Motion player_motion = { .x   = DEFAULT_PLAYER_X,   .y   = DEFAULT_PLAYER_Y,
                                    .dx  = DEFAULT_PLAYER_DX,  .dy  = DEFAULT_PLAYER_DY,
                                    .ddx = DEFAULT_PLAYER_DDX, .ddy = DEFAULT_PLAYER_DDY };

    Player player = { .motion = player_motion, .max_cur_jump_y = 0, .vertically_frozen = false,
                      .score  = DEFAULT_PLAYER_SCORE,
                      .skin   = DEFAULT_PLAYER_SKIN, .facing = DEFAULT_PLAYER_FACE_DIRECTION };


    return player;
}


//--------------------------------------------------

Return_code game_spawn_platforms_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Difficulty difficulty = game_get_difficulty_singleplayer (game);


    while (MAX_Y < game->data.camera_y + GAME_FIELD_HEIGHT * (1 + VERTICAL_PLATFORM_GENERATION_BUFFER_COEFFICIENT)) {

        Platform_type type = generate_platform_type (difficulty);
        if (!can_spawn_platform_type (game, difficulty, type)) continue;

        spawn_platform (game, difficulty, type);
    }


    return SUCCESS;
}


bool can_spawn_platform_type (Game* game, Difficulty difficulty, Platform_type type) {

    if (!game) { LOG_ERROR (BAD_ARGS); return false; }


    if (type == PT_FAKE && !can_spawn_fake_platform (game, difficulty)) return false;


    return true;
}


bool can_spawn_fake_platform (Game* game, Difficulty difficulty) {

    if (!game) { LOG_ERROR (BAD_ARGS); return false; }


    if (ABSOLUTE_MAX_NEW_PLATFORM_Y - MAX_Y < 2 * difficulty.min_platform_gap) return false;


    return true;
}


//--------------------------------------------------
#define DATA game->data.singleplayer

Difficulty game_get_difficulty_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return {}; }


    double score = list_get_player (game->engine.players.player_list, 0)->score;

    for (size_t i = 1; i < DATA.num_difficulties; i++) {

        if (score < DATA.difficulties [i].min_score) return DATA.difficulties [i - 1];
    }


    return DATA.difficulties [DATA.num_difficulties - 1];
}

#undef DATA
//--------------------------------------------------


Platform_type generate_platform_type (Difficulty difficulty) {

    double outcome              = random_scale (1);
    double prev_platform_border = 0;

    if (outcome < difficulty.default_platform_chance + prev_platform_border) return PT_DEFAULT;
    prev_platform_border += difficulty.default_platform_chance;

    if (outcome < difficulty.fake_platform_chance + prev_platform_border) return PT_FAKE;
    prev_platform_border += difficulty.fake_platform_chance;

    if (outcome < difficulty.moving_platform_chance + prev_platform_border) return PT_MOVING;
    prev_platform_border += difficulty.moving_platform_chance;

    if (outcome < difficulty.cloud_platform_chance + prev_platform_border) return PT_CLOUD;
    prev_platform_border += difficulty.cloud_platform_chance;


    return PT_DEFAULT;
}


Return_code spawn_platform (Game* game, Difficulty difficulty, Platform_type type) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (type) {

        case PT_DEFAULT: return spawn_default_platform (game, difficulty);
        case PT_MOVING:  return spawn_moving_platform  (game, difficulty);
        case PT_CLOUD:   return spawn_cloud_platform   (game, difficulty);
        case PT_FAKE:    return spawn_fake_platform    (game, difficulty);

        default: CODE_CRITICAL;
    }


    return SUCCESS;
}


Return_code spawn_default_platform (Game* game, Difficulty difficulty) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Point gaps = generate_gaps (difficulty);
    spawn_static_platform (game, gaps, PT_DEFAULT);


    return SUCCESS;
}


Return_code spawn_fake_platform (Game* game, Difficulty difficulty) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Point gaps = generate_gaps (difficulty);
    spawn_static_platform (game, gaps, PT_FAKE);


    return SUCCESS;
}


Return_code spawn_moving_platform (Game* game, Difficulty difficulty) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Point         gaps   = generate_gaps              (difficulty);
    Object_Motion motion = generate_platform_dynamics (difficulty, PT_MOVING);
    spawn_moving_platform (game, gaps, motion, PT_MOVING);


    return SUCCESS;
}


Return_code spawn_cloud_platform (Game* game, Difficulty difficulty) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Point gaps = generate_gaps (difficulty);
    spawn_static_platform (game, gaps, PT_CLOUD);


    return SUCCESS;
}


Return_code game_update_scores_camera_y_singleplayer (Game* game, double camera_distance) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_get_player (game->engine.players.player_list, 0)->score += camera_distance * CAMERA_Y_SCORE_COEFFICIENT;


    return SUCCESS;
}


Point generate_gaps (Difficulty difficulty) {

    double min_gap = difficulty.min_platform_gap;
    double max_gap = difficulty.max_platform_gap;


    return { .min = min_gap, .max = max_gap };
}


Object_Motion generate_platform_dynamics (Difficulty difficulty, Platform_type type) {

    if (type == PT_MOVING) return generate_moving_platform_dynamics (difficulty);


    LOG_ERROR (CRITICAL);
    return {};
}


Object_Motion generate_moving_platform_dynamics (Difficulty difficulty) {

    double min_dx   = difficulty.min_moving_platform_dx;
    double dx_range = difficulty.max_moving_platform_dx - difficulty.min_moving_platform_dx;
    double dx_value = min_dx + random_scale (dx_range);


    if (random_scale (1) >= 0.5) dx_value *= -1;


    return linear_dynamics (dx_value, 0);
}

