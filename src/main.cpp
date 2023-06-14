

//--------------------------------------------------

#include "game/hpp/game.hpp"

//--------------------------------------------------


int main (void) {

    srand ( (unsigned) time (nullptr));

    Game* game = create_game ();


    game_work (game);


    game_dtor (game);


    printf ("goodbye!\n");


    return 0;
}

