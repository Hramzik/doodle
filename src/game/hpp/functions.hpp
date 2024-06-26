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

SDL_Texture* game_get_sdl_texture
(Game* game, const char* path, bool transparent_flag = false, My_RGB clr = {});

Return_code game_load_media (Game* game);

Return_code game_load_player_skins        (Game* game);
Return_code game_load_platform_skins      (Game* game);
Return_code game_load_background_textures (Game* game);

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

int game_get_window_width  (Game* game);
int game_get_window_height (Game* game);


Return_code game_clear_screen  (Game* game);
Return_code game_set_drawcolor (Game* game, Uint8 r, Uint8 g, Uint8 b);
Return_code game_draw_rect     (Game* game, SDL_Rect rect);

Return_code game_render           (Game* game);
Return_code game_render_players   (Game* game);
Return_code game_render_platforms (Game* game);

Return_code      game_render_player          (Game* game, Player player);
Return_code      game_render_player_hitboxes (Game* game, Player player);
SDL_RendererFlip player_get_sdl_flip         (Player player, Player_Skin skin);

Return_code game_render_platform        (Game* game, Platform platform);
Return_code game_render_platform_hitbox (Game* game, Platform platform);

Return_code   game_render_background          (Game* game);
Return_code   game_render_true_background     (Game* game);
Object_Motion game_get_background_motion      (Game* game);
Object_Motion game_get_true_background_motion (Game* game);

Return_code game_draw_object_hitbox
(Game* game, Object_Motion coords, Array hitbox, bool flip_horizontally = false);

Return_code game_draw_object_hitbox_rect
(Game* game, Object_Motion coords, Hitbox_Rect hitbox_rect);

SDL_Texture* game_get_platform_texture        (Game* game, Platform platform);



SDL_Rect hitbox_rect_to_sdl_rect  (Hitbox_Rect rect);
SDL_Rect game_get_render_rect (Game* game, Object_Motion motion, SDL_Rect texture_offset);

//--------------------------------------------------
// keyboard_input

Return_code game_handle_keyboard_input (Game* game);

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

//--------------------------------------------------

// extern functions

#include "../../singleplayer/hpp/global_functions.hpp"
#include "../../list/hpp/list.hpp"


//--------------------------------------------------
#endif