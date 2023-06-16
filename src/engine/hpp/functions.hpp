#ifndef ENGINE_FUNCTIONS_HPP_INCLUDED
#define ENGINE_FUNCTIONS_HPP_INCLUDED
//--------------------------------------------------


#include "engine.hpp"


//--------------------------------------------------

// players

Return_code players_ctor (Players* players);
Return_code players_dtor (Players* players);
Return_code players_push (Players* players, Player player);
Return_code player_dump  (Player* player);

Return_code player_move_no_collision (Player* player, double t);
Return_code player_move_collision    (Player* player, Platform* platform, double t);

double players_get_min_player_y (Players* players);


//--------------------------------------------------

// platforms

Return_code platforms_ctor (Platforms* platforms);
Return_code platforms_push (Platforms* platforms, Platform platform);
Return_code platforms_dtor (Platforms* platforms);


//--------------------------------------------------

// engine

Return_code game_engine_ctor (Game_Engine* engine);
Return_code engine_data_ctor (Engine_Data* data);
Return_code game_engine_dtor (Game_Engine* engine);

Return_code engine_check_collisions                (Game_Engine* engine);
Return_code engine_check_player_collisions         (Game_Engine* engine, Player* player);
Return_code engine_check_player_platform_collision (Game_Engine* engine, Player* player, size_t platform_ind);

Return_code engine_move_objects (Game_Engine* engine);
Return_code engine_move_players (Game_Engine* engine);
Return_code engine_move_player  (Game_Engine* engine, Player* player);


//--------------------------------------------------

// motion

Object_Motion static_motion      (double x, double y);
Object_Motion linear_motion      (double x, double y, double dx, double dy);
Object_Motion linear_dynamics    (double dx, double dy);
Object_Motion quadratic_dynamics (double dx, double dy, double ddx, double ddy);


//--------------------------------------------------
#endif