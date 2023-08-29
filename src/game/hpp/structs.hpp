#ifndef GAME_STRUCTS_HPP_INCLUDED
#define GAME_STRUCTS_HPP_INCLUDED
//--------------------------------------------------


#include "enums.hpp"
#include "sdl.hpp"
#include "../../array/hpp/structs.hpp"
#include "../../singleplayer/hpp/structs.hpp"
#include "../../engine/hpp/structs2.hpp"


//--------------------------------------------------


typedef struct Point {

    double min;
    double max;

} Point; const size_t POINT_SIZE = sizeof (Point);


typedef struct My_RGB {

    unsigned char r;
    unsigned char g;
    unsigned char b;

} My_RGB; const size_t MY_RGB_SIZE = sizeof (My_RGB);


typedef struct Game_Media {

    Array platform_textures;
    Array background_textures;

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

    bool render_hitboxes;
    bool fullscreen;
    Game_background switching_background;

} Game_Conditions; const size_t GAME_CONDITIONS_SIZE = sizeof (Game_Conditions);


typedef struct Game_Data {

    int       high_score;
    Game_mode game_mode;
    double    camera_y;

    size_t background;
    size_t true_background;


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