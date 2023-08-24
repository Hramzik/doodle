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

Return_code engine_move_players     (Game_Engine* engine);
Return_code engine_move_player      (Game_Engine* engine, Player* player);
Return_code ensure_player_on_screen (Game_Engine* engine, Player* player);

Return_code engine_update_players (Game_Engine* engine);
Return_code player_update               (Player* player);
Return_code player_facing_update        (Player* player);
Return_code player_max_curjump_y_update (Player* player);

double players_get_min_player_y (Players* players);

//--------------------------------------------------
// platforms

Return_code platforms_ctor (Platforms* platforms);
Return_code platforms_dtor (Platforms* platforms);

Hitbox_Rect platform_get_true_hitbox_rect (Platform platform);
Hitbox_Rect get_platform_hitbox_rect      (void);


Return_code engine_move_platforms     (Game_Engine* engine);
Return_code engine_move_platform      (Game_Engine* engine, Platform* platform);
Return_code ensure_platform_on_screen (Game_Engine* engine, Platform* platform);

//--------------------------------------------------
// engine

Return_code game_engine_ctor (Game_Engine* engine);
Return_code engine_data_ctor (Engine_Data* data);
Return_code game_engine_dtor (Game_Engine* engine);

Return_code engine_check_collisions         (Game_Engine* engine);
Platform*   engine_check_player_collisions  (Game_Engine* engine, Player* player);

bool engine_check_player_platform_collision
(Game_Engine engine, Player player, Platform platform);

bool does_player_overlap_platform (Player player, Player_Skin skin, Platform platform);

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

bool     do_hitbox_rects_overlap            (Hitbox_Rect rect1, Hitbox_Rect rect2);
Return_code hitbox_rect_mirror_horizontally (Hitbox_Rect* rect);

//--------------------------------------------------
#endif