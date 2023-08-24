

//--------------------------------------------------

#include "../hpp/engine.hpp"

//--------------------------------------------------


Object_Motion static_motion (double x, double y) {

    Object_Motion motion;

    motion.x = x;
    motion.y = y;

    motion.dx  = 0;
    motion.dy  = 0;
    motion.ddx = 0;
    motion.ddy = 0;


    return motion;
}


Object_Motion linear_motion (double x, double y, double dx, double dy) {

    Object_Motion motion;

    motion.x = x;
    motion.y = y;

    motion.dx  = dx;
    motion.dy  = dy;
    motion.ddx = 0;
    motion.ddy = 0;


    return motion;
}


Object_Motion linear_dynamics (double dx, double dy) {

    Object_Motion motion;

    motion.x = 0;
    motion.y = 0;

    motion.dx  = dx;
    motion.dy  = dy;
    motion.ddx = 0;
    motion.ddy = 0;


    return motion;
}


Object_Motion quadratic_dynamics (double dx, double dy, double ddx, double ddy) {

    Object_Motion motion;

    motion.x = 0;
    motion.y = 0;

    motion.dx  = dx;
    motion.dy  = dy;
    motion.ddx = ddx;
    motion.ddy = ddy;


    return motion;
}


Return_code motion_copy_dynamics (Object_Motion src, Object_Motion* dst) {

    if (!dst) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    dst->dx  = src.dx;
    dst->dy  = src.dy;
    dst->ddx = src.ddx;
    dst->ddy = src.ddy;


    return SUCCESS;
}


Return_code motion_copy_dynamics (Object_Motion* src, Object_Motion* dst) {

    if (!src) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!dst) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return motion_copy_dynamics (*src, dst);
}


Return_code motion_update (Object_Motion* motion, double t) {

    if (!motion) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    motion_update_x_part (motion, t);
    motion_update_y_part (motion, t);


    return SUCCESS;
}


Return_code motion_update_x_part (Object_Motion* motion, double t) {

    if (!motion) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    motion->x  += motion->dx  * t + motion->ddx * t * t / 2;
    motion->dx += motion->ddx * t;


    return SUCCESS;
}


Return_code motion_update_y_part (Object_Motion* motion, double t) {

    if (!motion) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    motion->y  += motion->dy  * t + motion->ddy * t * t / 2;
    motion->dy += motion->ddy * t;


    return SUCCESS;
}


Return_code motion_ensure_x_le_than (Object_Motion* motion, double value) {

    if (!motion) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (motion->x <= value) return SUCCESS;


    double extra_x = motion->x - value;
    motion->x -= 2 * extra_x;


    motion->dx *= -1;


    return SUCCESS;
}


Return_code motion_ensure_x_ge_than (Object_Motion* motion, double value) {

    if (!motion) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (motion->x >= value) return SUCCESS;


    double extra_x = value - motion->x;
    motion->x += 2 * extra_x;


    motion->dx *= -1;


    return SUCCESS;
}


Hitbox_Rect motion_get_true_hitbox_rect (Object_Motion motion, Hitbox_Rect rect) {

    Hitbox_Rect true_rect = {};

    true_rect.x = motion.x + rect.x;
    true_rect.y = motion.y + rect.y;

    true_rect.w = rect.w;
    true_rect.h = rect.h;


    return true_rect;
}

