#ifndef GAME_STRUCTS_HPP_INCLUDED
#define GAME_STRUCTS_HPP_INCLUDED
//--------------------------------------------------

#include "game.hpp"

//--------------------------------------------------

// extern structs

#include "../../singleplayer/hpp/structs.hpp"


//--------------------------------------------------


typedef struct Point {

    double min;
    double max;

} Point; const size_t POINT_SIZE = sizeof (Point);


typedef struct Game_Media {

    SDL_Texture** doodler_textures;
    size_t        doodler_textures_count;

    Array platform_textures;

    SDL_Texture** background_textures;
    size_t        background_textures_count;

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

    int       high_score;
    Game_mode game_mode;
    double    camera_y;

    Singleplayer_Data singleplayer;

} Game_Data; const size_t GAME_DATA_SIZE = sizeof (Game_Data);


typedef struct Game {

    Game_Output output;

    Game_Media media;

    Game_Data data;

    Game_Conditions conditions;

    Game_Engine engine;

} Game; const size_t GAME_SIZE = sizeof (Game);


//--------------------------------------------------
#endif