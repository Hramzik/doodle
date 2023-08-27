#ifndef ENGINE_CONSTANTS_INCLUDED
#define ENGINE_CONSTANTS_INCLUDED
//--------------------------------------------------


#include <stdio.h>


//------------------ settings ----------------------


const size_t MAX_PLAYERS_COUNT   = 2;
const size_t MAX_PLATFORMS_COUNT = 10000;


//--------------------------------------------------


const double DEFAULT_FIELD_WIDTH  = 600;
const double DEFAULT_FIELD_HEIGHT = 800;


const double DEFAULT_UPDATE_TIME = 0.45;


const double PLAYER_DY_AFTER_COLLISION = 1.75;


const double PLAYER_HITBOX_LEFT_WIDTH  = 30;
const double PLAYER_HITBOX_RIGHT_WIDTH = 15;
const double PLAYER_HITBOX_HEIGHT      = 67;


const double PLATFORM_HITBOX_WIDTH = 110;
const double PLATFORM_HITBOX_HEIGHT = 28;


//--------------------------------------------------
#endif