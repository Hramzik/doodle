

//--------------------------------------------------

#include "../hpp/engine.hpp"

//--------------------------------------------------


Return_code players_push (Players* players, Player player) {

    if (!players) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (players->count == MAX_PLAYERS_COUNT) { LOG_ERROR (CRITICAL); return CRITICAL; }


    players->buffer [players->count] = player;
    players->count += 1;


    return SUCCESS;
}


Return_code player_dump (Player* player) {

    if (!player) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Object_Motion motion = player->motion;


    printf ("dumping player..\n");
    printf ("x,   y:   %5.2lf %5.2lf\n", motion.x,   motion.y);
    printf ("dx,  dy:  %5.2lf %5.2lf\n", motion.dx,  motion.dy);
    printf ("ddx, ddy: %5.2lf %5.2lf\n", motion.ddx, motion.ddy);


    return SUCCESS;
}


double players_get_min_player_y (Players* players) {

    if (!players) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    double min_player_y = 0;


    for (size_t i = 0; i < players->count; i++) {

        if (min_player_y < players->buffer [i].motion.y) {

            min_player_y = players->buffer [i].motion.y;
        }
    }


    return min_player_y;
}


