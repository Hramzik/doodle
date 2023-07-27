#ifndef GAME_FUNCTIONS_HPP_INCLUDED
#define GAME_FUNCTIONS_HPP_INCLUDED
//--------------------------------------------------

#include "game.hpp"

//--------------------------------------------------

// c-dtors

Return_code initialize_sdl (void);
Return_code quit_sdl       (void);

Game*       create_game            (void);
Return_code game_output_ctor     (Game_Output* output);
Return_code game_media_ctor      (Game_Media* media);
Return_code game_conditions_ctor (Game_Conditions* conditions);
Return_code game_data_ctor       (Game_Data* data);

Return_code game_dtor        (Game* game);
Return_code game_output_dtor (Game_Output* game);
Return_code game_media_dtor  (Game_Media* media);

//--------------------------------------------------

// game_media

Return_code game_load_media (Game* game);
Return_code game_media_push_doodler_texture    (Game_Media* media, SDL_Texture* texture);
Return_code game_media_push_platform_texture   (Game_Media* media, SDL_Texture* texture);
Return_code game_media_push_background_texture (Game_Media* media, SDL_Texture* texture);

Return_code game_load_doodler_textures    (Game* game);
Return_code game_load_platform_textures   (Game* game);
Return_code game_load_background_textures (Game* game);

Return_code game_load_doodler_texture    (Game* game, const char* path);
Return_code game_load_platform_texture   (Game* game, const char* path);
Return_code game_load_background_texture (Game* game, const char* path);


//--------------------------------------------------

// game

Return_code game_spawn_objects   (Game* game);
Return_code game_spawn_players   (Game* game);
Return_code game_spawn_platforms (Game* game);
Return_code game_add_player   (Game* game, Player player);
Return_code game_add_platform (Game* game, Platform platform);
Return_code game_despawn_objects   (Game* game);
Return_code game_despawn_platforms (Game* game);

Return_code game_work (Game* game);

Return_code game_update         (Game* game);
Return_code game_move_camera    (Game* game);
Return_code game_mirror_players (Game* game);
Return_code game_mirror_player  (Game* game, Player* player);

Return_code game_update_scores_camera_y (Game* game, double camera_disance);


//--------------------------------------------------

// render

Return_code game_render            (Game* game);
Return_code game_render_players    (Game* game);
Return_code game_render_platforms  (Game* game);
Return_code game_render_player     (Game* game, Player* player);
Return_code game_render_platform   (Game* game, Platform* platform);
Return_code game_render_background (Game* game);


//--------------------------------------------------

// keyboard_input

Return_code game_handle_keyboard_input              (Game* game);
Return_code game_handle_keyboard_input_singleplayer (Game* game);
Return_code game_handle_keydown_singleplayer (Game* game, SDL_Event event);
Return_code game_handle_keyup_singleplayer   (Game* game, SDL_Event event);
Return_code game_handle_left_down_singleplayer  (Game* game);
Return_code game_handle_right_down_singleplayer (Game* game);
Return_code game_handle_a_down_singleplayer     (Game* game);
Return_code game_handle_d_down_singleplayer     (Game* game);
Return_code game_handle_left_up_singleplayer  (Game* game);
Return_code game_handle_right_up_singleplayer (Game* game);
Return_code game_handle_a_up_singleplayer     (Game* game);
Return_code game_handle_d_up_singleplayer     (Game* game);


//--------------------------------------------------

// support functions

double random_scale (double input);

//--------------------------------------------------

// extern functions

#include "../../singleplayer/hpp/global_functions.hpp"


//--------------------------------------------------
#endif