#ifndef ENGINE_STRUCTS2_HPP_INCLUDED
#define ENGINE_STRUCTS2_HPP_INCLUDED
//--------------------------------------------------


// этот файл создан, тк для Players нужен List, для которого нужен Player


//--------------------------------------------------


#include "../../list/hpp/structs.hpp"
#include "../../array/hpp/structs.hpp"


//--------------------------------------------------


typedef struct Players {

    List  list;
    Array skins;

} Players; const size_t PLAYERS_SIZE = sizeof (Players);


//--------------------------------------------------


typedef struct Platforms_Data {

    double min_y;
    double max_y;
    double max_material_y;

    size_t cur_default_skin;
    size_t cur_moving_skin;
    size_t cur_fake_skin;
    size_t cur_cloud_skin;

} Platforms_Data; const size_t PLATFORMS_DATA_SIZE = sizeof (Platforms_Data);


typedef struct Platforms {

    List  list;
    Array skins;

    Platforms_Data data;

} Platforms; const size_t PLATFORMS_SIZE = sizeof (Platforms);


//--------------------------------------------------


typedef struct Game_Engine {

    Players players;

    Platforms platforms;

    Engine_Data data;

} Game_Engine; const size_t GAME_ENGINE_SIZE = sizeof (Game_Engine);


//--------------------------------------------------
#endif