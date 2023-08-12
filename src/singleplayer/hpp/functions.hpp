#ifndef SINGLEPLAYER_FUNCTIONS_HPP_INCLUDED
#define SINGLEPLAYER_FUNCTIONS_HPP_INCLUDED
//--------------------------------------------------


#include "singleplayer.hpp"


//--------------------------------------------------
// spawners

Return_code spawn_platform         (Game* game, Difficulty difficulty, Platform_type type);
Return_code spawn_default_platform (Game* game, Difficulty difficulty);
Return_code spawn_fake_platform    (Game* game, Difficulty difficulty);
Return_code spawn_moving_platform  (Game* game, Difficulty difficulty);
Return_code spawn_cloud_platform   (Game* game, Difficulty difficulty);

bool can_spawn_platform_type (Game* game, Difficulty difficulty, Platform_type type);
bool can_spawn_fake_platform (Game* game, Difficulty difficulty);

//--------------------------------------------------
// generators

Player        generate_default_player           (Game* game);
Platform_type generate_platform_type            (Difficulty difficulty);
Point         generate_gaps                     (Difficulty difficulty);
Object_Motion generate_platform_dynamics        (Difficulty difficulty, Platform_type type);
Object_Motion generate_moving_platform_dynamics (Difficulty difficulty);

//--------------------------------------------------
// other

Difficulty  game_get_difficulty_singleplayer (Game* game);


//--------------------------------------------------
#endif