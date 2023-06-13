#ifndef GAME_DSL_ON
#define GAME_DSL_ON
//--------------------------------------------------


#define TOP_PIC     (game->media.top_pic)
#define BOTTOM_PIC  (game->media.bottom_pic)
#define RESULT_PIC  (game->media.result_pic)
#define MY_RENDERER (game->output.renderer)

//--------------------------------------------------

#else
#undef GAME_DSL_ON


#undef TOP_PIC
#undef BOTTOM_PIC
#undef RESULT_PIC
#undef MY_RENDERER


//--------------------------------------------------
#endif