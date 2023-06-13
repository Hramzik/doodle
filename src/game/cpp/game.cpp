

//--------------------------------------------------


#include "../hpp/game.hpp"


//--------------------------------------------------


Return_code game_load_media (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_load_doodler_textures  (game);
    game_load_platform_textures (game);


    return SUCCESS;
}



Return_code game_work (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_load_media


    


    while(true) {

    //--------------------------------------------------
        game_update_conditions (game);

        if (game->conditions.exit) break;

        game_handle_conditions (game);
    //--------------------------------------------------


        game_generate_picture (game);


        SDL_RenderClear (game->output.renderer);
        game_render_picture (game);
        SDL_RenderPresent (game->output.renderer);


        fps_handler_next_frame (fps_counter);
        fps_handler_print (fps_counter);
    }


    fps_handler_dtor (fps_counter);


    return SUCCESS;
}


Return_code game_generate_picture (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    game_update_window_size_and_result (game);


    for (size_t i = 0; i < PICTURE_GENERATIONS_COUNT; i++) {

        merge_pictures (&RESULT_PIC, &TOP_PIC, &BOTTOM_PIC, game->data.top_pic_offset);
    }


    return SUCCESS;
}



Return_code game_render_picture (Game* game) {

    if (!game) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    SDL_Texture* result_texture = game_generate_result_texture (game);


    SDL_RenderCopy (game->output.renderer, result_texture, nullptr, nullptr);


    SDL_DestroyTexture (result_texture);


    return SUCCESS;
}



