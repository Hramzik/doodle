#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED
//--------------------------------------------------


#include "time.h"


//--------------------------------------------------


#include "../../lib/types/Return_code.hpp"


//--------------------------------------------------


typedef struct Timer {

    clock_t start_time;
    size_t  frame_number;

    clock_t frame_start_time;
    clock_t last_frame_delay;

} Timer; const size_t TIMER_SIZE = sizeof (Timer);


//--------------------------------------------------


Timer*      timer_ctor  (void);
Return_code timer_dtor  (Timer* timer);
Return_code timer_reset (Timer* timer);

double timer_get_total_delay_h  (Timer* timer);
double timer_get_total_delay_m  (Timer* timer);
double timer_get_total_delay_s  (Timer* timer);
double timer_get_total_delay_ms (Timer* timer);

double timer_get_last_frame_delay_h  (Timer* timer);
double timer_get_last_frame_delay_m  (Timer* timer);
double timer_get_last_frame_delay_s  (Timer* timer);
double timer_get_last_frame_delay_ms (Timer* timer);
double timer_get_fps                 (Timer* timer);

double timer_get_frame_time_h  (Timer* timer);
double timer_get_frame_time_m  (Timer* timer);
double timer_get_frame_time_s  (Timer* timer);
double timer_get_frame_time_ms (Timer* timer);


Return_code timer_next_frame (Timer* timer);

Return_code timer_print_fps (Timer* timer);
Return_code timer_print_last_frame_delay_ms (Timer* timer);


//--------------------------------------------------
#endif