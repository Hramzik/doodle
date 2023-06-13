#ifndef PLAYERS_HPP_INCLUDED
#define PLAYERS_HPP_INCLUDED
//--------------------------------------------------


typedef struct Player {

    Object_Motion motion;

    int   score;
    size_t skin;

} Player; const size_t PLAYER_SIZE = sizeof (Player);


typedef struct Players {

    Player* buffer;

    size_t count;

} Players; const size_t PLAYERS_SIZE = sizeof (Players);


//--------------------------------------------------


Return_code players_push (Players* players, Player player);


//--------------------------------------------------
#endif