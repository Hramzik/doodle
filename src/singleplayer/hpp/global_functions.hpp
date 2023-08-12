#ifndef SINGLEPLAYER_GLOBAL_FUNCTIONS_HPP_INCLUDED
#define SINGLEPLAYER_GLOBAL_FUNCTIONS_HPP_INCLUDED
//--------------------------------------------------


#include "structs.hpp"


//--------------------------------------------------
// c-dtors

Return_code singleplayer_data_ctor (Singleplayer_Data* data);

//--------------------------------------------------
// spawners

Return_code game_spawn_players_singleplayer   (Game* game);
Return_code game_spawn_platforms_singleplayer (Game* game);

//--------------------------------------------------
// other

Return_code game_update_scores_camera_y_singleplayer (Game* game, double camera_distance);
Return_code game_teleport_mid_singleplayer     (Game* game);
Return_code game_fly_up_singleplayer_launch    (Game* game);
Return_code game_fly_up_singleplayer_terminate (Game* game);
Return_code game_freeze_singleplayer_launch    (Game* game);
Return_code game_freeze_singleplayer_terminate (Game* game);
Return_code game_switch_player_texture_direction_singleplayer (Game* game);


//--------------------------------------------------
#endif