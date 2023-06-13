#ifndef COMMON_FIELD_HPP_INCLUDED
#define COMMON_FIELD_HPP_INCLUDED
//--------------------------------------------------


#include "includes.hpp"
#include "constants.hpp"


//--------------------------------------------------


typedef struct Object_Motion {

    double x;
    double y;

    double dx;
    double dy;

    double ddx;
    double ddy;

} Object_Motion; const size_t OBJECT_MOTION_SIZE = sizeof (Object_Motion);


//--------------------------------------------------


#include "players.hpp"
#include "platforms.hpp"


//--------------------------------------------------


typedef struct Game_Field {

    Players players;

    Platforms platforms;

} Game_Field; const size_t GAME_FIELD_SIZE = sizeof (Game_Field);


//--------------------------------------------------


Return_code players_ctor    (Players*    players);
Return_code platforms_ctor  (Platforms*  platforms);
Return_code game_field_ctor (Game_Field* field);

Return_code players_dtor    (Players*    players);
Return_code platforms_dtor  (Platforms*  platforms);
Return_code game_field_dtor (Game_Field* field);


//--------------------------------------------------
#endif