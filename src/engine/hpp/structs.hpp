#ifndef ENGINE_STRUCTS_HPP_INCLUDED
#define ENGINE_STRUCTS_HPP_INCLUDED
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

    int   score;
    size_t skin;

    int platform_hit_ind;

} Player; const size_t PLAYER_SIZE = sizeof (Player);


typedef struct Players {

    Player* buffer;

    size_t count;

} Players; const size_t PLAYERS_SIZE = sizeof (Players);


//--------------------------------------------------


typedef struct Platform {

    Object_Motion motion;

    Platform_type type;

} Platform; const size_t PLATFORM_SIZE = sizeof (Platform);


typedef struct Platforms {

    Platform* buffer;

    size_t count;

    int min_y;
    int max_y;

} Platforms; const size_t PLATFORMS_SIZE = sizeof (Platforms);


//--------------------------------------------------


typedef struct Engine_Data {

    double t; // for updating

} Engine_Data; const size_t ENGINE_DATA_SIZE = sizeof (Engine_Data);



typedef struct Game_Engine {

    Players players;

    Platforms platforms;

    Engine_Data data;

} Game_Engine; const size_t GAME_ENGINE_SIZE = sizeof (Game_Engine);


//--------------------------------------------------
#endif