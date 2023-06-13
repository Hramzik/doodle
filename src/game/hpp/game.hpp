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

Game*       game_ctor            (void);
Return_code game_output_ctor     (Game_Output* output);
Return_code game_media_ctor      (Game_Media* media);
Return_code game_conditions_ctor (Game_Conditions* conditions);
Return_code game_data_ctor       (Game_Data* data);

Return_code game_dtor        (Game* game);
Return_code game_output_dtor (Game_Output* game);
Return_code game_media_dtor  (Game_Media* media);

//--------------------------------------------------







//--------------------------------------------------
#endif