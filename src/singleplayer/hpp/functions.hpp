#ifndef SINGLEPLAYER_FUNCTIONS_HPP_INCLUDED
#define SINGLEPLAYER_FUNCTIONS_HPP_INCLUDED
//--------------------------------------------------


#include "singleplayer.hpp"


//--------------------------------------------------

Player      generate_default_player          (Game* game);
int         game_get_difficulty_singleplayer (Game* game);
Return_code spawn_platform                   (Game* game, int difficulty, Platform_type type);

Platform    generate_static_platform  (Game* game, double min_gap, double max_gap, Platform_type type);
Return_code spawn_static_platform     (Game* game, double min_gap, double max_gap, Platform_type type);
/*static Platform    generate_default_platform (Game* game, double min_gap, double max_gap);
static Platform    generate_cloud_platform   (Game* game, double min_gap, double max_gap);
static Platform    generate_fake_platform    (Game* game, double min_gap, double max_gap);
*/

Platform_type generate_platform_type             (int difficulty);
Platform_type generate_platform_type_difficuly_0 (void);


Return_code spawn_platform_difficulty_0 (Game* game, Platform_type type);

//--------------------------------------------------
#endif