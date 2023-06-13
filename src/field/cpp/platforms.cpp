

//--------------------------------------------------

#include "../hpp/field.hpp"

//--------------------------------------------------


Return_code platforms_push (Platforms* platforms, Platform platform) {

    if (!platforms) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (platforms->count == MAX_PLATFORMS_COUNT) { LOG_ERROR (CRITICAL); return CRITICAL; }


    platforms->buffer [platforms->count] = platform;
    platforms->count += 1;


    return SUCCESS;
}

