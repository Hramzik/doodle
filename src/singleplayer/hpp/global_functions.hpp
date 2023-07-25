#ifndef SINGLEPLAYER_GLOBAL_FUNCTIONS_HPP_INCLUDED
#define SINGLEPLAYER_GLOBAL_FUNCTIONS_HPP_INCLUDED
//--------------------------------------------------


#include "structs.hpp"


//--------------------------------------------------


Return_code game_spawn_players_singleplayer   (Game* game);
Return_code game_spawn_platforms_singleplayer (Game* game);

Return_code singleplayer_data_ctor (Singleplayer_Data* data);

Return_code game_update_scores_camera_y_singleplayer (Game* game, double camera_distance);

Return_code game_teleport_up_singleplayer (Game* game);


//--------------------------------------------------
#endif