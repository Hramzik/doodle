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
// keyboard input

Return_code game_handle_keyboard_input_singleplayer (Game* game);

//--------------------------------------------------
// score

Return_code game_update_scores_camera_y_singleplayer (Game* game, double camera_distance);

//--------------------------------------------------
#endif