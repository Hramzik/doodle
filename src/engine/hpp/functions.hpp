#ifndef ENGINE_FUNCTIONS_HPP_INCLUDED
#define ENGINE_FUNCTIONS_HPP_INCLUDED
//--------------------------------------------------


#include "engine.hpp"
#include "../../array/hpp/array.hpp"
#include "../../list/hpp/list.hpp"


//--------------------------------------------------
// players

Return_code players_ctor (Players* players);
Return_code players_dtor (Players* players);
Return_code player_dump  (Player* player);

Return_code engine_move_players            (Game_Engine* engine);
Platform*   engine_check_player_collisions (Game_Engine* engine, Player* player);
Return_code engine_update_players          (Game_Engine* engine);

double players_get_min_player_y (Players* players);

Hitbox_Rect player_get_true_hitbox_rect (Player player, Player_Skin skin, size_t index);

Player_Skin engine_get_player_skin (Game_Engine engine, Player player);

//--------------------------------------------------
// platforms

Return_code platforms_ctor (Platforms* platforms);
Return_code platforms_dtor (Platforms* platforms);

Return_code engine_move_platforms (Game_Engine* engine);

Return_code   platforms_data_update_cur_skins
    (Platforms_Data* data, Array platform_types, size_t skin);

Platform_Skin engine_get_platform_skin      (Game_Engine engine, Platform platform);
Platform_Skin engine_get_platform_type_skin (Game_Engine engine, Platform_type type);

//--------------------------------------------------
// engine

Return_code game_engine_ctor (Game_Engine* engine);
Return_code game_engine_dtor (Game_Engine* engine);


//--------------------------------------------------
// motion

Object_Motion static_motion      (double x, double y);
Object_Motion linear_motion      (double x, double y, double dx, double dy);
Object_Motion linear_dynamics    (double dx, double dy);
Object_Motion quadratic_dynamics (double dx, double dy, double ddx, double ddy);

Return_code motion_copy_dynamics (Object_Motion  src, Object_Motion* dst);
Return_code motion_copy_dynamics (Object_Motion* src, Object_Motion* dst);

Return_code motion_update        (Object_Motion* motion, double t);
Return_code motion_update_x_part (Object_Motion* motion, double t);
Return_code motion_update_y_part (Object_Motion* motion, double t);

Return_code motion_ensure_x_le_than (Object_Motion* motion, double value);
Return_code motion_ensure_x_ge_than (Object_Motion* motion, double value);

Hitbox_Rect motion_get_true_hitbox_rect (Object_Motion motion, Hitbox_Rect rect);

//--------------------------------------------------
// other

Return_code hitbox_rect_mirror_horizontally (Hitbox_Rect* rect);

//--------------------------------------------------
#endif