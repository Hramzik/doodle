#ifndef SINGLEPLAYER_CONSTANTS_HPP_INCLUDED
#define SINGLEPLAYER_CONSTANTS_HPP_INCLUDED
//--------------------------------------------------


#include "difficulty_0.hpp"
#include "difficulty_1.hpp"
#include "difficulty_2.hpp"
#include "difficulty_3.hpp"
#include "difficulty_4.hpp"
#include "difficulty_5.hpp"


//--------------------------------------------------
// players


const double DEFAULT_PLAYER_X   = DEFAULT_WINDOW_WIDTH / 2;
const double DEFAULT_PLAYER_Y   = DEFAULT_WINDOW_HEIGHT * 3 / 6;
const double DEFAULT_PLAYER_DX  = 0;
const double DEFAULT_PLAYER_DY  = 2.2;
const double DEFAULT_PLAYER_DDX = 0;
const double DEFAULT_PLAYER_DDY = -0.007;

const size_t DEFAULT_PLAYER_SKIN  = 2;
const size_t DEFAULT_PLAYER_SCORE = 0;

const double CAMERA_Y_SCORE_COEFFICIENT = 0.4;
//--------------------------------------------------
// platforms

//---------------
const size_t MAX_DIFFICULTY_SCORES_START_LINE = __LINE__;

const double DIFFICULTY_0_MAX_SCORE = 0; // test difficulty
const double DIFFICULTY_1_MAX_SCORE = 300;
const double DIFFICULTY_2_MAX_SCORE = 3500;
const double DIFFICULTY_3_MAX_SCORE = 7000;
const double DIFFICULTY_4_MAX_SCORE = 9500;
const double DIFFICULTY_5_MAX_SCORE = 18000;

const size_t NUM_DIFFICULTIES = __LINE__ - MAX_DIFFICULTY_SCORES_START_LINE; // с запасом в три линии
//----------------


const double ABSOLUTE_MAX_PLATFORM_GAP = 210;


//--------------------------------------------------
#endif