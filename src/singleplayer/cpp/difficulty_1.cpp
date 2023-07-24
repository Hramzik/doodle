

//--------------------------------------------------

#include "../hpp/singleplayer.hpp"

//--------------------------------------------------


Platform_type generate_platform_type_difficuly_1 (void) {

    double outcome              = random_scale (1);
    double prev_platform_border = 0;

    if (outcome < DIFFICULTY_0_DEFAULT_PLATFORM_CHANCE + prev_platform_border) return PT_DEFAULT;
    if (outcome < DIFFICULTY_0_FAKE_PLATFORM_CHANCE    + prev_platform_border) return PT_FAKE;
}


