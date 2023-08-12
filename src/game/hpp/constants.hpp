#ifndef GAME_CONSTANTS_INCLUDED
#define GAME_CONSTANTS_INCLUDED
//--------------------------------------------------


#include "game.hpp"


//--------------------------------------------------
// settings

const int DEFAULT_WINDOW_WIDTH  = 800; // int because of int field in SDL_rect
const int DEFAULT_WINDOW_HEIGHT = 800;

const size_t PICTURE_GENERATIONS_COUNT = 1;

const double MAX_UPDATE_TIME = 0.5;

//--------------------------------------------------

const Uint32 GAME_OUTPUT_FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;


const size_t SIZE_T_SIZE = sizeof (size_t);
const size_t CHAR_SIZE   = sizeof (char);

//--------------------------------------------------
// skins


const size_t DOODLER_SKIN_PATHS_START_LINE = __LINE__;

#define DOODLER_SKIN1_PATH  "media/doodler1.png"
#define DOODLER_SKIN2_PATH  "media/doodler2.png"
#define DOODLER_SKIN3_PATH  "media/doodler3.png"

const size_t DEFAULT_DOODLER_TEXTURES_COUNT = __LINE__ - DOODLER_SKIN_PATHS_START_LINE; // с запасом 3

//--------------------------------------------------

const size_t PLATFORM_SKIN_PATHS_START_LINE = __LINE__;

#define PLATFORM_SKIN1_PATH "media/platform.png"
#define PLATFORM_SKIN2_PATH "media/platform_fake.png"
#define PLATFORM_SKIN3_PATH "media/platform_cloud.png"

const size_t DEFAULT_PLATFORM_TEXTURES_COUNT = __LINE__ - PLATFORM_SKIN_PATHS_START_LINE;

//--------------------------------------------------

const size_t BACKGROUND_SKIN_PATHS_START_LINE = __LINE__;

#define BACKGROUND1_PATH "media/background1.png"
#define BACKGROUND2_PATH "media/background2.jpg"

const size_t DEFAULT_BACKGROUND_TEXTURES_COUNT = __LINE__ - BACKGROUND_SKIN_PATHS_START_LINE;


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


const int PLATFORM_TEXTURE_WIDTH  = (int) PLATFORM_HITBOX_WIDTH;
const int PLATFORM_TEXTURE_HEIGHT = (int) PLATFORM_HITBOX_HEIGHT;


//--------------------------------------------------
#endif