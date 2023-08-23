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

SDL_Texture* game_get_sdl_texture (Game* game, const char* path);

Return_code game_load_media (Game* game);
Return_code game_media_push_doodler_texture    (Game_Media* media, SDL_Texture* texture);
Return_code game_media_push_platform_texture   (Game_Media* media, SDL_Texture* texture);
Return_code game_media_push_background_texture (Game_Media* media, SDL_Texture* texture);

Return_code game_load_player_skins        (Game* game);
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

Return_code game_update                 (Game* game);
Return_code game_update_no_time_control (Game* game);

Return_code game_move_camera            (Game* game);
Return_code game_update_scores_camera_y (Game* game, double camera_disance);

//--------------------------------------------------
// render

Return_code game_clear_screen  (Game* game);
Return_code game_set_drawcolor (Game* game, Uint8 r, Uint8 g, Uint8 b);
Return_code game_draw_rect     (Game* game, SDL_Rect rect);

Return_code game_render           (Game* game);
Return_code game_render_players   (Game* game);
Return_code game_render_platforms (Game* game);

Return_code      game_render_player        (Game* game, Player* player);
Return_code      game_render_player_hitbox (Game* game, Player* player);
SDL_RendererFlip player_get_sdl_flip       (Player* player);

Return_code game_render_platform        (Game* game, Platform* platform);
Return_code game_render_platform_hitbox (Game* game, Platform* platform);

Return_code   game_render_background     (Game* game);
Object_Motion game_get_background_motion (Game* game);

Return_code game_render_object_hitbox_rect
(Game* game, Object_Motion coords, Hitbox_Rect hitbox_rect);

SDL_Texture* game_get_platform_texture   (Game* game, Platform* platform);
SDL_Texture* game_get_background_texture (Game* game);

int          game_get_window_width     (Game* game);
int          game_get_window_height    (Game* game);

SDL_Rect get_player_texture_offset (Player* player);
SDL_Rect get_hitbox_rect_offset  (Hitbox_Rect rect);
SDL_Rect get_platform_texture_offset (void);
SDL_Rect get_platform_hitbox_offset  (void);
SDL_Rect get_background_texture_offset (Game* game);

SDL_Rect game_get_render_rect (Game* game, Object_Motion* motion, SDL_Rect texture_offset);

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

Return_code game_handle_comma_up    (Game* game);
Return_code game_handle_period_up (Game* game);

//--------------------------------------------------
// platforms

Return_code game_add_platform (Game* game, Platform platform);
Return_code update_max_y      (Game* game, Platform platform);

Platform    generate_static_platform (Game* game, Point gaps, Platform_type type);
Return_code spawn_static_platform    (Game* game, Point gaps, Platform_type type);
Return_code spawn_moving_platform    (Game* game, Point gaps, Object_Motion dynamics, Platform_type type);

//--------------------------------------------------

// other functions

double random_scale (double input);
Return_code hitbox_rect_mirror_horizontally (Hitbox_Rect* rect);

//--------------------------------------------------

// extern functions

#include "../../singleplayer/hpp/global_functions.hpp"


//--------------------------------------------------
#endif