#ifndef SINGLEPLAYER_FUNCTIONS_HPP_INCLUDED
#define SINGLEPLAYER_FUNCTIONS_HPP_INCLUDED
//--------------------------------------------------


#include "singleplayer.hpp"


//--------------------------------------------------


Return_code game_spawn_players_singleplayer   (Game* game);
Return_code game_spawn_platforms_singleplayer (Game* game);

int game_get_difficulty_singleplayer (Game* game);


//--------------------------------------------------
#endif