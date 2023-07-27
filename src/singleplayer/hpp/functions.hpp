#ifndef SINGLEPLAYER_FUNCTIONS_HPP_INCLUDED
#define SINGLEPLAYER_FUNCTIONS_HPP_INCLUDED
//--------------------------------------------------


#include "singleplayer.hpp"


//--------------------------------------------------

Player      generate_default_player          (Game* game);
Difficulty  game_get_difficulty_singleplayer (Game* game);
Return_code spawn_platform                   (Game* game, int difficulty, Platform_type type);

Platform    generate_static_platform (Game* game, double min_gap, double max_gap, Platform_type type);
Return_code spawn_static_platform    (Game* game, double min_gap, double max_gap, Platform_type type);
Return_code update_max_y             (Game* game, Platform platform);
/*static Platform    generate_default_platform (Game* game, double min_gap, double max_gap);
static Platform    generate_cloud_platform   (Game* game, double min_gap, double max_gap);
static Platform    generate_fake_platform    (Game* game, double min_gap, double max_gap);
*/

Platform_type generate_platform_type (Difficulty difficulty);


Return_code spawn_platform         (Game* game, Difficulty difficulty, Platform_type type);
Return_code spawn_default_platform (Game* game, Difficulty difficulty);
Return_code spawn_fake_platform    (Game* game, Difficulty difficulty);
Return_code spawn_moving_platform  (Game* game, Difficulty difficulty);
Return_code spawn_cloud_platform   (Game* game, Difficulty difficulty);

bool can_spawn_platform_type (Game* game, Difficulty difficulty, Platform_type type);
bool can_spawn_fake_platform (Game* game, Difficulty difficulty);

//--------------------------------------------------
#endif