#ifndef ENGINE_STRUCTS2_HPP_INCLUDED
#define ENGINE_STRUCTS2_HPP_INCLUDED
//--------------------------------------------------


// этот файл создан, тк для Players нужен List, для которого нужен Player


//--------------------------------------------------


#include "engine.hpp"


//--------------------------------------------------


typedef struct Players {

    List list;

} Players; const size_t PLAYERS_SIZE = sizeof (Players);


typedef struct Platforms {

    List list;

    double min_y;
    double max_y;

} Platforms; const size_t PLATFORMS_SIZE = sizeof (Platforms);


typedef struct Game_Engine {

    Players players;

    Platforms platforms;

    Engine_Data data;

} Game_Engine; const size_t GAME_ENGINE_SIZE = sizeof (Game_Engine);


//--------------------------------------------------
#endif