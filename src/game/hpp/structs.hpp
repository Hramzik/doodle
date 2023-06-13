#ifndef GAME_STRUCTS_HPP_INCLUDED
#define GAME_STRUCTS_HPP_INCLUDED
//--------------------------------------------------

#include "game.hpp"

//--------------------------------------------------


typedef struct Game_Media {

    SDL_Texture** doodler_textures;
    size_t        doodler_textures_count;

    SDL_Texture** platform_textures;
    size_t        platform_textures_count;

} Game_Media; const size_t GAME_MEDIA_SIZE = sizeof (Game_Media);


typedef struct Game_Output {

    SDL_Window* window;

    SDL_Renderer* renderer;

} Game_Output; const size_t GAME_OUTPUT_SIZE = sizeof (Game_Output);


typedef struct Game_Conditions {

    bool exit;

    bool pressed_a;
    bool pressed_d;

    bool pressed_left;
    bool pressed_right;

} Game_Conditions; const size_t GAME_CONDITIONS_SIZE = sizeof (Game_Conditions);


typedef struct Game_Data {

    int high_score = 0;
    Game_mode game_mode;

} Game_Data; const size_t GAME_DATA_SIZE = sizeof (Game_Data);



//--------------------------------------------------
#endif