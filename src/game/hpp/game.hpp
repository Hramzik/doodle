#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
//--------------------------------------------------


#include "../../field/hpp/field.hpp"


//--------------------------------------------------


#define  SDL_MAIN_HANDLED // no argc, argv
#include "../../../../../../lib/SDL2/include/SDL2/SDL.h" // for VSC to highlight everything before compile time
#include "../../../../../../lib/SDL2/include/SDL2/SDL_image.h"

//--------------------------------------------------

#include "toggle_dsl.hpp"

//--------------------------------------------------

#include "enums.hpp"
#include "constants.hpp"
#include "structs.hpp"

//--------------------------------------------------


typedef struct Game {

    Game_Output output;

    Game_Media media;

    Game_Data data;

    Game_Conditions conditions;

    Game_Field field;

} Game; const size_t GAME_SIZE = sizeof (Game);


//--------------------------------------------------


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

Return_code game_load_media (Game* game);
Return_code game_media_push_doodler_texture  (Game_Media* media, SDL_Texture* texture);
Return_code game_media_push_platform_texture (Game_Media* media, SDL_Texture* texture);
Return_code game_load_doodler_textures       (Game* game);
Return_code game_load_doodler_texture        (Game* game, const char* path);
Return_code game_load_platform_textures      (Game* game);
Return_code game_load_platform_texture       (Game* game, const char* path);


Return_code game_spawn_players (Game* game);
Return_code game_spawn_player  (Game* game, double x, double y, size_t skin);

Return_code game_work (Game* game);

Return_code game_render          (Game* game);
Return_code game_render_player   (Game* game, Player* player);
Return_code game_render_platform (Game* game, Platform* platform);


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
#endif