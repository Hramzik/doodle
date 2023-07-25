#ifndef ENGINE_CONSTANTS_INCLUDED
#define ENGINE_CONSTANTS_INCLUDED
//--------------------------------------------------


#include "engine.hpp"


//------------------ settings ----------------------


const size_t MAX_PLAYERS_COUNT   = 2;
const size_t MAX_PLATFORMS_COUNT = 10000;


//--------------------------------------------------


const double DEFAULT_UPDATE_TIME = 0.1;


const double PLAYER_DY_AFTER_COLLISION = 1.75;


const int DOODLER_HITBOX_LEFT_WIDTH  = 30; // int because of int in SDL_Rect
const int DOODLER_HITBOX_RIGHT_WIDTH = 15; // int because of int in SDL_Rect
const int DOODLER_HITBOX_HEIGHT      = 92;


const int PLATFORM_WIDTH = 105;
const int PLATFORM_HEIGHT = 30;


//--------------------------------------------------
#endif