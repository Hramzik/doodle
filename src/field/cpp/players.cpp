

//--------------------------------------------------

#include "../hpp/field.hpp"

//--------------------------------------------------


Return_code players_push (Players* players, Player player) {

    if (!players) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (players->count == MAX_PLAYERS_COUNT) { LOG_ERROR (CRITICAL); return CRITICAL; }


    players->buffer [players->count] = player;
    players->count += 1;


    return SUCCESS;
}

