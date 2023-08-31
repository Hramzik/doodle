#ifndef ENGINE_STRUCTS_HPP_INCLUDED
#define ENGINE_STRUCTS_HPP_INCLUDED
//--------------------------------------------------


#include "enums.hpp"
#include "../../game/hpp/sdl.hpp"
#include "../../array/hpp/structs.hpp"


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


typedef struct Hitbox_Rect {

    double x; // bottom left
    double y;
    double w;
    double h;

} Hitbox_Rect; const size_t HITBOX_RECT_SIZE = sizeof (Hitbox_Rect);


//--------------------------------------------------


typedef struct Player_Skin {

    Player_face_direction default_face_direction;
    SDL_Texture* texture;
    SDL_Rect texture_offset;

    Array legs_hitbox;
    Array good_hitbox;

} Player_Skin; const size_t PLAYER_SKIN_SIZE = sizeof (Player_Skin);


//--------------------------------------------------


typedef struct Platform_Skin {

    Array platform_types;

    SDL_Texture* texture;
    SDL_Rect texture_offset;

    Array hitbox;

} Platform_Skin; const size_t PLATFORM_SKIN_SIZE = sizeof (Platform_Skin);


//--------------------------------------------------


typedef struct Player {

    Object_Motion motion;
    double max_cur_jump_y;
    bool vertically_frozen;

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