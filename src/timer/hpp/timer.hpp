#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED
//--------------------------------------------------


#include "time.h"


//--------------------------------------------------


#include "../../lib/types/Return_code.hpp"


//--------------------------------------------------


typedef struct Timer {

    clock_t start_time;

} Timer; const size_t TIMER_SIZE = sizeof (Timer);


//--------------------------------------------------


Timer*      timer_ctor  (void);
Return_code timer_dtor  (Timer* timer);
Return_code timer_reset (Timer* timer);

size_t timer_get_total_delay_h  (Timer* timer);
size_t timer_get_total_delay_m  (Timer* timer);
size_t timer_get_total_delay_s  (Timer* timer);
size_t timer_get_total_delay_ms (Timer* timer);


//--------------------------------------------------
#endif