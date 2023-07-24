#ifndef SINGLEPLAYER_CONSTANTS_HPP_INCLUDED
#define SINGLEPLAYER_CONSTANTS_HPP_INCLUDED
//--------------------------------------------------
// players


const double DEFAULT_PLAYER_X   = DEFAULT_WINDOW_WIDTH / 2;
const double DEFAULT_PLAYER_Y   = DEFAULT_WINDOW_HEIGHT * 3 / 6;
const double DEFAULT_PLAYER_DX  = 0;
const double DEFAULT_PLAYER_DY  = 2.2;
const double DEFAULT_PLAYER_DDX = 0;
const double DEFAULT_PLAYER_DDY = -0.007;

const size_t DEFAULT_PLAYER_SKIN  = 1;
const size_t DEFAULT_PLAYER_SCORE = 0;


//--------------------------------------------------
// platforms

const int MAX_DIFFICULTY_0_SCORE = 1000;
const int MAX_DIFFICULTY_1_SCORE = 2000;



const double DIFFICULTY_0_MIN_PLATFORM_GAP = 60;
const double DIFFICULTY_1_MIN_PLATFORM_GAP = 90;
const double DIFFICULTY_2_MIN_PLATFORM_GAP = 120;

const double DIFFICULTY_0_MAX_PLATFORM_GAP = 100;
const double DIFFICULTY_1_MAX_PLATFORM_GAP = 150;
const double DIFFICULTY_2_MAX_PLATFORM_GAP = 200;


const double DIFFICULTY_0_DEFAULT_PLATFORM_CHANCE = 1;

const double DIFFICULTY_1_DEFAULT_PLATFORM_CHANCE = 0.9;
const double DIFFICULTY_1_FAKE_PLATFORM_CHANCE    = 0.1;

const double DIFFICULTY_2_DEFAULT_PLATFORM_CHANCE = 0.7;
const double DIFFICULTY_2_FAKE_PLATFORM_CHANCE    = 0.1;
const double DIFFICULTY_2_MOVING_PLATFORM_CHANCE  = 0.2;

const double DIFFICULTY_3_DEFAULT_PLATFORM_CHANCE = 0.4;
const double DIFFICULTY_3_FAKE_PLATFORM_CHANCE    = 0.1;
const double DIFFICULTY_3_MOVING_PLATFORM_CHANCE  = 0.4;
const double DIFFICULTY_3_CLOUD_PLATFORM_CHANCE   = 0.1;


//--------------------------------------------------
#endif