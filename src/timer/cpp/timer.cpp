

//--------------------------------------------------


#include "../hpp/timer.hpp"


//--------------------------------------------------


#include "../../lib/logs.hpp"


//--------------------------------------------------


Timer* timer_ctor (void) {

    Timer* timer = (Timer*) calloc (TIMER_SIZE, 1);


    timer->start_time   = clock ();
    timer->frame_number = 0;

    timer->frame_start_time = 0;
    timer->last_frame_delay = 0;


    return timer;
}


Return_code timer_dtor  (Timer* timer) {

    if (!timer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    free (timer);


    return SUCCESS;
}


Return_code timer_reset (Timer* timer) {

    if (!timer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    timer->start_time = clock ();


    return SUCCESS;
}


Return_code timer_next_frame (Timer* timer) {

    if (!timer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    timer->frame_number += 1;

    timer->last_frame_delay = clock() - timer->frame_start_time;
    timer->frame_start_time = clock();


    return SUCCESS;
}


size_t timer_get_fps (Timer* timer) {

    return (size_t) (1 / (double) timer_get_last_frame_delay_s (timer));
}


Return_code timer_print_fps (Timer* timer) {

    if (!timer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    printf ("fps: %zd\n", timer_get_fps (timer));


    return SUCCESS;
}


Return_code timer_print_last_frame_delay_ms (Timer* timer) {

    if (!timer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    printf ("last frame delay: %zd ms\n", timer_get_last_frame_delay_ms (timer));


    return SUCCESS;
}


size_t timer_get_total_delay_h (Timer* timer) {

    return timer_get_total_delay_m (timer) / 60;
}


size_t timer_get_total_delay_m (Timer* timer) {

    return timer_get_total_delay_s (timer) / 60;
}


size_t timer_get_total_delay_s (Timer* timer) {

    return timer_get_total_delay_ms (timer) / 1000;
}


size_t timer_get_total_delay_ms  (Timer* timer) {

    if (!timer) { LOG_ERROR (BAD_ARGS); return 0; }


    return 1000 * (clock() - timer->start_time) / CLOCKS_PER_SEC;
}


size_t timer_get_last_frame_delay_h  (Timer* timer) {

    if (!timer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return timer_get_last_frame_delay_m (timer) / 60;
}


size_t timer_get_last_frame_delay_m  (Timer* timer) {

    if (!timer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return timer_get_last_frame_delay_s (timer) / 60;
}


size_t timer_get_last_frame_delay_s  (Timer* timer) {

    if (!timer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return timer_get_last_frame_delay_ms (timer) / 1000;
}


size_t timer_get_last_frame_delay_ms (Timer* timer) {

    if (!timer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    return 1000 * timer->last_frame_delay / CLOCKS_PER_SEC;
}


size_t timer_get_frame_time_h (Timer* timer) {

    return timer_get_frame_time_m (timer) / 60;
}


size_t timer_get_frame_time_m (Timer* timer) {

    return timer_get_frame_time_s (timer) / 60;
}


size_t timer_get_frame_time_s (Timer* timer) {

    return timer_get_frame_time_ms (timer) / 1000;
}


size_t timer_get_frame_time_ms (Timer* timer) {

    if (!timer) { LOG_ERROR (BAD_ARGS); return 0; }


    return 1000 * (clock() - timer->frame_start_time) / CLOCKS_PER_SEC;
}
