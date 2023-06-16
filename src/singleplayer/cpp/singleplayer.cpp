

//--------------------------------------------------

#include "../hpp/singleplayer.hpp"

//--------------------------------------------------



Return_code game_spawn_platforms_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    int difficulty = game_get_difficulty (game);


    Platform_type type = game_get_platform_type (difficulty);


    spawn_platform (game, difficulty, type);

    while (game->engine.platforms.max_y < game->data.camera_y + DEFAULT_WINDOW_HEIGHT * (1 + VERTICAL_PLATFORM_GENERATION_BUFFER_COEFFICIENT)) {

        
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


static Return_code spawn_platform (Game* game, int difficulty, Platform_type type) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    switch (difficulty) {

        case 0: return spawn_platform_difficulty_0 (game, type);
        case 1: return spawn_platform_difficulty_1 (game, type);
        case 2: return spawn_platform_difficulty_2 (game, type);
        default: break;
    }


    return SUCCESS;
}


Return_code game_spawn_players_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (game->engine.players.count >= 1) return SUCCESS;


    game_spawn_player (game, DEFAULT_WINDOW_WIDTH / 2, DEFAULT_WINDOW_HEIGHT * 3 / 6, DEFAULT_PLAYER_SKIN - 1);


    return SUCCESS;
}


Return_code game_get_platform_type (int difficulty) {


}




Return_code spawn_static_platform (Game* game, double min_gap, double max_gap, Platfom_type type) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    double min_x = PLATFORM_WIDTH / 2;
    double     x = min_x + random_scale (DEFAULT_WINDOW_WIDTH - PLATFORM_WIDTH);

    double min_y = min_gap + game->engine.platforms.max_y;
    double     y = min_y + random_scale (max_gap - min_gap);


    Object_Motion motion = static_motion (x, y);
    Platform platform = { .motion = motion, .type = type };
    platforms_push (&game->engine.platforms, platform);


    game->engine.platforms.max_y = (int) y;


    return SUCCESS;
}


Return_code spawn_default_platform (Game* game, double min_gap, double max_gap) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return spawn_static_platform (game, min_gap, max_gap, PT_DEFAULT);
}


Return_code spawn_cloud_platform (Game* game, double min_gap, double max_gap) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return spawn_static_platform (game, min_gap, max_gap, PT_CLOUD);
}


Return_code spawn_fake_platform (Game* game, double min_gap, double max_gap) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return spawn_static_platform (game, min_gap, max_gap, PT_FAKE);
}


Return_code spawn_moving_platform (Game* game, double min_gap, double max_gap, Object_Motion dynamics) {

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