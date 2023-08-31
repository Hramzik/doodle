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
// players


const double BIG_HORIZONTAL_STEP   = 2;
const double SMALL_HORIZONTAL_STEP = 1;

//--------------------------------------------------
// platforms


const size_t PLATFORM_TYPES_COUNT = 1;
const double VERTICAL_PLATFORM_GENERATION_BUFFER_COEFFICIENT = 0;


//--------------------------------------------------
// background

const size_t DEFAULT_BACKGROUND      = 0;
const size_t DEFAULT_TRUE_BACKGROUND = 5;

//--------------------------------------------------
#endif