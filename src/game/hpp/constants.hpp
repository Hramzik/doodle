#ifndef GAME_CONSTANTS_INCLUDED
#define GAME_CONSTANTS_INCLUDED
//--------------------------------------------------


#include "game.hpp"


//------------------ settings ----------------------


const size_t DEFAULT_WINDOW_WIDTH  = 800;
const size_t DEFAULT_WINDOW_HEIGHT = 800;

const size_t PICTURE_GENERATIONS_COUNT = 1;

const size_t DEFAULT_DOODLER_TEXTURES_COUNT  = 10;
const size_t DEFAULT_PLATFORM_TEXTURES_COUNT = 10;


//--------------------------------------------------


const Uint32 GAME_OUTPUT_FLAGS = SDL_WINDOW_SHOWN;


const size_t SIZE_T_SIZE = sizeof (size_t);
const size_t CHAR_SIZE   = sizeof (char);


#define DOODLER_SKIN1_PATH  "media/doodler1.png"
#define PLATFORM_SKIN1_PATH "media/platform1.png"

const double BIG_HORIZONTAL_STEP   = 1;
const double SMALL_HORIZONTAL_STEP = 1;
//--------------------------------------------------
#endif