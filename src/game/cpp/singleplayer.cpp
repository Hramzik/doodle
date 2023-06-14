

//--------------------------------------------------

#include "../hpp/game.hpp"

//--------------------------------------------------



Return_code game_spawn_platforms_singleplayer (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    //int difficulty = game_get_difficulty_singleplayer (game);


    //double chances [PLATFORM_TYPES_COUNT];


    //game_fill_platform_chances (game, chances, difficulty);


    //game_get_platform_type


    while (game->engine.platforms.max_y < game->data.camera_y + DEFAULT_WINDOW_HEIGHT * (1 + VERTICAL_PLATFORM_GENERATION_BUFFER_COEFFICIENT)) {

        double min_x = PLATFORM_WIDTH / 2;
        double     x = min_x            + (double) rand () / RAND_MAX * (DEFAULT_WINDOW_WIDTH - PLATFORM_WIDTH);

        double min_y = MIN_PLATFORM_GAP + game->engine.platforms.max_y;
        double     y = min_y            + (double) rand () / RAND_MAX * (MAX_PLATFORM_GAP - MAX_PLATFORM_GAP);

        Object_Motion motion = static_motion (x, y);
        Platform platform = { .motion = motion };
        platforms_push (&game->engine.platforms, platform);


        game->engine.platforms.max_y = (int) y;
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

