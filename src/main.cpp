

//--------------------------------------------------

#include "game/hpp/game.hpp"

//--------------------------------------------------


int main (void) {

    srand ( (unsigned) time (nullptr));
    initialize_sdl ();

    Game* game = create_game ();


    game_work (game);


    game_dtor (game);


    printf ("goodbye!\n");

    quit_sdl ();
    return 0;
}

