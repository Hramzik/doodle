#ifndef COMMON_PLATFORMS_INCLUDED
#define COMMON_PLATFORMS_INCLUDED
//--------------------------------------------------


typedef struct Platform {

    bool          moving;
    Object_Motion motion;

    bool cloud;
    bool fragile;
    bool shadow;

} Platform; const size_t PLATFORM_SIZE = sizeof (Platform);


typedef struct Platforms {

    Platform* buffer;

    size_t count;

    int min_y;
    int max_y;

} Platforms; const size_t PLATFORMS_SIZE = sizeof (Platforms);


//--------------------------------------------------


Return_code platforms_push (Platforms* platforms, Platform platform);


//--------------------------------------------------
#endif