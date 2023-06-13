

//--------------------------------------------------

#include "../hpp/game.hpp"

//--------------------------------------------------


Return_code initialize_sdl (void) {

    if(SDL_Init (SDL_INIT_VIDEO) < 0){

        LOG_MESSAGE ("SDL could not initialize!\n");
        return LIB_ERR;
    }


    if (!SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "1")) {

        LOG_MESSAGE ("Error: Linear texture filtering not enabled!");
        return LIB_ERR;
    }


    int imgFlags = IMG_INIT_PNG;

    if(!(IMG_Init (imgFlags) & imgFlags)) {

        LOG_MESSAGE ("SDL_image could not initialize!\n");
        return LIB_ERR;
    }


    return SUCCESS;
}


Return_code quit_sdl (void) {


    SDL_Quit ();
    IMG_Quit ();


    return SUCCESS;
}


Return_code game_output_ctor (Game_Output* output) {

    if (!output) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    output->window = SDL_CreateWindow ("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                           DEFAULT_WINDOW_WIDTH,    DEFAULT_WINDOW_HEIGHT, 
                                           GAME_OUTPUT_FLAGS); // empty header

    if(!output->window) {

        LOG_MESSAGE ("Window could not be created!\n");
        return LIB_ERR;
    }


    //--------------------------------------------------


    output->renderer = SDL_CreateRenderer(output->window, -1, SDL_RENDERER_ACCELERATED);

    if (!output->renderer) {

        LOG_MESSAGE ("Renderer could not be created!");
        return LIB_ERR;
    }


    return SUCCESS;
}


Return_code game_output_dtor (Game_Output* output) {

    if (!output) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (output->renderer) SDL_DestroyRenderer (output->renderer);
    if (output->window)   SDL_DestroyWindow   (output->window);


    return SUCCESS;
}


Return_code game_conditions_ctor (Game_Conditions* conditions) {

    if (!conditions) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    conditions->exit = false;


    return SUCCESS;
}


Return_code game_media_ctor (Game_Media* media) {

    if (!media) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    media->doodler_textures  = (SDL_Texture**) calloc (DEFAULT_DOODLER_TEXTURES_COUNT,  sizeof (SDL_Texture*));
    media->platform_textures = (SDL_Texture**) calloc (DEFAULT_PLATFORM_TEXTURES_COUNT, sizeof (SDL_Texture*));


    media->doodler_textures_count  = DEFAULT_DOODLER_TEXTURES_COUNT;
    media->platform_textures_count = DEFAULT_PLATFORM_TEXTURES_COUNT;


    return SUCCESS;
}


Return_code game_media_dtor (Game_Media* media) {

    if (!media) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < media->doodler_textures_count; i++) {

        SDL_DestroyTexture (media->doodler_textures [i]);
    }

    for (size_t i = 0; i < media->platform_textures_count; i++) {

        SDL_DestroyTexture (media->platform_textures [i]);
    }


    free (media->doodler_textures);
    free (media->platform_textures);


    return SUCCESS;
}


Return_code game_data_ctor (Game_Data* data) {

    if (!data) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    data->high_score = 0;
    data->game_mode = SINGLE_PLAYER;


    return SUCCESS;
}


Game* game_ctor (void) {

    Game* game = (Game*) calloc (1, GAME_SIZE);


    game_output_ctor     (&game->output);
    game_media_ctor      (&game->media);
    game_data_ctor       (&game->data);
    game_conditions_ctor (&game->conditions);
    game_field_ctor      (&game->field);


    return game;
}


Return_code game_dtor (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_output_dtor (&game->output);
    game_media_dtor  (&game->media);
    game_field_dtor  (&game->field);


    free (game);


    return SUCCESS;
}
