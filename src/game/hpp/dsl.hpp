#ifndef GAME_DSL_HPP_INCLUDED
#define GAME_DSL_HPP_INCLUDED
//--------------------------------------------------



#define MAX_Y                       game->engine.platforms.data.max_y
#define MAX_MATERIAL_Y              game->engine.platforms.data.max_material_y
#define ABSOLUTE_MAX_NEW_PLATFORM_Y MAX_MATERIAL_Y + ABSOLUTE_MAX_PLATFORM_GAP
#define PLATFORM_Y                  platform.motion.y


#define GAME_WINDOW_WIDTH            game_get_window_width  (game)
#define GAME_WINDOW_HEIGHT           game_get_window_height (game)
#define GAME_FIELD_WIDTH             game->engine.data.field_width
#define GAME_FIELD_HEIGHT            game->engine.data.field_height
#define GAME_FIELD_WIDTH_INT  (int) (game->engine.data.field_width)
#define GAME_FIELD_HEIGHT_INT (int) (game->engine.data.field_height)

#define RENDER_HITBOXES game->conditions.render_hitboxes


//--------------------------------------------------
#endif