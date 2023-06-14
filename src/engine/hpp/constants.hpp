#ifndef ENGINE_CONSTANTS_INCLUDED
#define ENGINE_CONSTANTS_INCLUDED
//--------------------------------------------------


#include "engine.hpp"


//------------------ settings ----------------------


const size_t MAX_PLAYERS_COUNT   = 2;
const size_t MAX_PLATFORMS_COUNT = 10000;


//--------------------------------------------------


const double DEFAULT_UPDATE_TIME = 0.1;
const double DEFAULT_PLAYER_DY   = 2.2;
const double DEFAULT_PLAYER_DDY  = -0.007;

const double PLAYER_DY_AFTER_COLLISION = 1.75;


const int DOODLER_WIDTH  = 75; // int because of int in SDL_Rect
const int DOODLER_HEIGHT = 75;


const int PLATFORM_WIDTH = 105;
const int PLATFORM_HEIGHT = 30;


//--------------------------------------------------
#endif