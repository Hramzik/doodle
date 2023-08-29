#ifndef GAME_CONSTANTS_INCLUDED
#define GAME_CONSTANTS_INCLUDED
//--------------------------------------------------


#include "game.hpp"


//--------------------------------------------------
// settings

const int DEFAULT_WINDOW_WIDTH  = 800; // int because of int field in SDL_rect
const int DEFAULT_WINDOW_HEIGHT = DEFAULT_FIELD_HEIGHT;

const size_t PICTURE_GENERATIONS_COUNT = 1;

const double MAX_UPDATE_TIME = 0.5;

//--------------------------------------------------

const Uint32 GAME_OUTPUT_FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;


const size_t SIZE_T_SIZE = sizeof (size_t);
const size_t CHAR_SIZE   = sizeof (char);

//--------------------------------------------------

#define PLATFORM_SKIN1_PATH "media/platform.png"
#define PLATFORM_SKIN2_PATH "media/platform_fake.png"
#define PLATFORM_SKIN3_PATH "media/platform_cloud.png"

//--------------------------------------------------
// players


const double BIG_HORIZONTAL_STEP   = 2;
const double SMALL_HORIZONTAL_STEP = 1;


const int PLAYER_TEXTURE_WIDTH  = 92;
const int PLAYER_TEXTURE_HEIGHT = 67;

//--------------------------------------------------
// platforms


const size_t PLATFORM_TYPES_COUNT = 1;

const double VERTICAL_PLATFORM_GENERATION_BUFFER_COEFFICIENT = 0;


const int PLATFORM_TEXTURE_WIDTH  = 115;
const int PLATFORM_TEXTURE_HEIGHT = 30;


//--------------------------------------------------
#endif