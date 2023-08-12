#ifndef SINGLEPLAYER_STRUCTS_HPP_INCLUDED
#define SINGLEPLAYER_STRUCTS_HPP_INCLUDED
//--------------------------------------------------


typedef struct Difficulty {

    int min_score;

    double max_platform_gap;
    double min_platform_gap;

    double default_platform_chance;
    double    fake_platform_chance;
    double  moving_platform_chance;
    double   cloud_platform_chance;

    double max_moving_platform_dx;
    double min_moving_platform_dx;

} Difficulty; const size_t DIFFICULTY_SIZE = sizeof (Difficulty);


typedef struct Singleplayer_Data {

    Difficulty* difficulties;
    size_t num_difficulties;

} Singleplayer_Data; const size_t SINGLEPLAYER_DATA_SIZE = sizeof (Singleplayer_Data);


//--------------------------------------------------
#endif