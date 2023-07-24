

//--------------------------------------------------

#include "../hpp/singleplayer.hpp"

//--------------------------------------------------


Return_code game_spawn_players_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->engine.players.count >= 1) return SUCCESS;


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
                      .skin = DEFAULT_PLAYER_SKIN - 1, .platform_hit_ind = -1 };


    return player;
}


Return_code game_spawn_platforms_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    int difficulty = game_get_difficulty_singleplayer (game);


    while (game->engine.platforms.max_y < game->data.camera_y + DEFAULT_WINDOW_HEIGHT * (1 + VERTICAL_PLATFORM_GENERATION_BUFFER_COEFFICIENT)) {

        Platform_type type = generate_platform_type (difficulty);
        spawn_platform (game, difficulty, type);
    }


    return SUCCESS;
}


int game_get_difficulty_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return 0; }


    int score = game->engine.players.buffer [0].score;

    if (score < MAX_DIFFICULTY_0_SCORE) return 0;
    if (score < MAX_DIFFICULTY_1_SCORE) return 1;


    return 2;
}


Return_code spawn_platform (Game* game, int difficulty, Platform_type type) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (difficulty) {

        case 0: return spawn_platform_difficulty_0 (game, type);
        case 1: //return spawn_platform_difficulty_1 (game, type);
        case 2: //return spawn_platform_difficulty_2 (game, type);

        default: LOG_ERROR (CRITICAL); return CRITICAL;
    }


    return SUCCESS;
}


Platform_type generate_platform_type (int difficulty) {

    switch (difficulty) {

        case 0: return generate_platform_type_difficuly_0 ();
        case 1: //return generate_platform_type_difficuly_1 ();
        case 2: //return generate_platform_type_difficuly_2 ();

        default: LOG_ERROR (BAD_ARGS); return PT_DEFAULT;
    }


    return PT_DEFAULT;
}


Platform generate_static_platform (Game* game, double min_gap, double max_gap, Platform_type type) {

    if (!game) LOG_ERROR (BAD_ARGS);


    double min_x = PLATFORM_WIDTH / 2;
    double     x = min_x + random_scale (DEFAULT_WINDOW_WIDTH - PLATFORM_WIDTH);

    double min_y = min_gap + game->engine.platforms.max_y;
    double     y = min_y + random_scale (max_gap - min_gap);


    Object_Motion motion   = static_motion (x, y);
    Platform      platform = { .motion = motion, .type = type };


    return platform;
}


Return_code spawn_static_platform (Game* game, double min_gap, double max_gap, Platform_type type) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Platform platform = generate_static_platform (game, min_gap, max_gap, type);
    game_add_platform (game, platform);
    game->engine.platforms.max_y = platform.motion.y;


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
    platforms_push (&game->engine.platforms, platform);


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