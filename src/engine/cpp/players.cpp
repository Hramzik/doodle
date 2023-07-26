

//--------------------------------------------------

#include "../hpp/engine.hpp"

//--------------------------------------------------


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


    for (Node* node = players->list.first; node; node = node->next) {

        Player* player = node_get_player (node);

        if (min_player_y < player->motion.y) {

            min_player_y = player->motion.y;
        }
    }


    return min_player_y;
}


