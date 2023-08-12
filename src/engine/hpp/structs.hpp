#ifndef ENGINE_STRUCTS_HPP_INCLUDED
#define ENGINE_STRUCTS_HPP_INCLUDED
//--------------------------------------------------


#include "enums.hpp"


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


typedef struct Player {

    Object_Motion motion;

    double score;
    size_t skin;

    Player_face_direction facing;

} Player; const size_t PLAYER_SIZE = sizeof (Player);



//--------------------------------------------------


typedef struct Platform {

    Object_Motion motion;

    Platform_type type;

    bool dead;

} Platform; const size_t PLATFORM_SIZE = sizeof (Platform);


//--------------------------------------------------


typedef struct Engine_Data {

    double t; // for updating

    double field_width;
    double field_height;

} Engine_Data; const size_t ENGINE_DATA_SIZE = sizeof (Engine_Data);


//--------------------------------------------------
#endif