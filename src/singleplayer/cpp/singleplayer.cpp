

//--------------------------------------------------

#include "../hpp/singleplayer.hpp"

//--------------------------------------------------


Return_code game_spawn_players_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->engine.players.list.len >= 1) return SUCCESS;


    Player player = generate_default_player (game);
    game_add_player (game, player);


    return SUCCESS;
}


Player generate_default_player (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); }


    Object_Motion player_motion = { .x   = DEFAULT_PLAYER_X,   .y   = DEFAULT_PLAYER_Y,
                                    .dx  = DEFAULT_PLAYER_DX,  .dy  = DEFAULT_PLAYER_DY,
                                    .ddx = DEFAULT_PLAYER_DDX, .ddy = DEFAULT_PLAYER_DDY };

    Player player = { .motion = player_motion, .score = DEFAULT_PLAYER_SCORE,
                      .skin = DEFAULT_PLAYER_SKIN - 1 };


    return player;
}


//--------------------------------------------------
#define MAX_Y                       game->engine.platforms.max_y
#define MAX_MATERIAL_Y              game->engine.platforms.max_material_y
#define ABSOLUTE_MAX_NEW_PLATFORM_Y MAX_MATERIAL_Y + ABSOLUTE_MAX_PLATFORM_GAP
#define PLATFORM_Y                  platform.motion.y

Return_code game_spawn_platforms_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Difficulty difficulty = game_get_difficulty_singleplayer (game);


    while (MAX_Y < game->data.camera_y + DEFAULT_WINDOW_HEIGHT * (1 + VERTICAL_PLATFORM_GENERATION_BUFFER_COEFFICIENT)) {

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


    double score = list_get_player (game->engine.players.list, 0)->score;

    for (size_t i = 0; i < DATA.num_difficulties; i++) {

        if (score < DATA.difficulties [i].max_score) return DATA.difficulties [i];
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


Platform generate_static_platform (Game* game, double min_gap, double max_gap, Platform_type type) {

    if (!game) LOG_ERROR (BAD_ARGS);


    double min_x = PLATFORM_WIDTH / 2;
    double     x = min_x + random_scale (DEFAULT_WINDOW_WIDTH - PLATFORM_WIDTH);

    double min_y = min_gap + MAX_Y;
    max_gap      = fmin (max_gap, ABSOLUTE_MAX_NEW_PLATFORM_Y - MAX_Y);
    double     y = min_y + random_scale (max_gap - min_gap);


    Object_Motion motion   = static_motion (x, y);
    Platform      platform = { .motion = motion, .type = type, .dead = false };


    return platform;
}


Return_code spawn_static_platform (Game* game, double min_gap, double max_gap, Platform_type type) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Platform platform = generate_static_platform (game, min_gap, max_gap, type);
    game_add_platform (game, platform);


    if (PLATFORM_Y > MAX_Y) MAX_Y = PLATFORM_Y;
    if (type == PT_FAKE) return SUCCESS;

    if (PLATFORM_Y > MAX_MATERIAL_Y) MAX_MATERIAL_Y = PLATFORM_Y;


    return SUCCESS;
}

#undef MAX_Y
#undef MAX_MATERIAL_Y
#undef PLATFORM_Y
//--------------------------------------------------


Return_code spawn_default_platform (Game* game, Difficulty difficulty) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    spawn_static_platform (game, difficulty.min_platform_gap, difficulty.max_platform_gap, PT_DEFAULT);


    return SUCCESS;
}


Return_code spawn_fake_platform (Game* game, Difficulty difficulty) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    spawn_static_platform (game, difficulty.min_platform_gap, difficulty.max_platform_gap, PT_FAKE);


    return SUCCESS;
}


Return_code spawn_moving_platform (Game* game, Difficulty difficulty) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    spawn_static_platform (game, difficulty.min_platform_gap, difficulty.max_platform_gap, PT_MOVING);


    return SUCCESS;
}


Return_code spawn_cloud_platform (Game* game, Difficulty difficulty) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    spawn_static_platform (game, difficulty.min_platform_gap, difficulty.max_platform_gap, PT_CLOUD);


    return SUCCESS;
}


Return_code game_update_scores_camera_y_singleplayer (Game* game, double camera_distance) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_get_player (game->engine.players.list, 0)->score += camera_distance * CAMERA_Y_SCORE_COEFFICIENT;


    return SUCCESS;
}


Return_code game_teleport_up_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    list_get_player (game->engine.players.list, 0)->motion.x = DEFAULT_WINDOW_WIDTH / 2;
    list_get_player (game->engine.players.list, 0)->motion.y = game->data.camera_y + DEFAULT_WINDOW_HEIGHT * 3 / 7;

    list_get_player (game->engine.players.list, 0)->motion.dy = 0;


    return SUCCESS;
}


/*
Platform generate_default_platform (Game* game, double min_gap, double max_gap) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return generate_static_platform (game, min_gap, max_gap, PT_DEFAULT);
}


Platform generate_cloud_platform (Game* game, double min_gap, double max_gap) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return generate_static_platform (game, min_gap, max_gap, PT_CLOUD);
}


Platform generate_fake_platform (Game* game, double min_gap, double max_gap) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return generate_static_platform (game, min_gap, max_gap, PT_FAKE);
}*/

/*
Platform spawn_moving_platform (Game* game, double min_gap, double max_gap, Object_Motion dynamics) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    double min_x = PLATFORM_WIDTH / 2;
    double     x = min_x + random_scale (DEFAULT_WINDOW_WIDTH - PLATFORM_WIDTH);

    double min_y = min_gap + game->engine.platforms.max_y;
    double     y = min_y + random_scale (max_gap - min_gap);


    Object_Motion motion = static_motion (x, y);
    Platform platform = { .motion = motion, .type = PT_MOVING };


    game->engine.platforms.max_y = (int) y;


    return SUCCESS;
}


Return_code spawn_linear_moving_platform (Game* game, double min_gap, double max_gap, double dx, double dy) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return spawn_moving_platform (game, min_gap, max_gap, linear_dynamics (dx, dy));
}


Return_code spawn_linear_horizontally_moving_platform (Game* game, double min_gap, double max_gap, double dx) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return spawn_linear_moving_platform (game, min_gap, max_gap, dx, 0);
}


Return_code generate_linear_horizontally_moving_platform (Game* game, double min_gap, double max_gap, double min_dx, double max_dx) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    double dx = min_y + random_scale (max_gap - min_gap);


    return spawn_linear_horizontally_moving_platform (game, min_gap, max_gap);
}

*/