

//--------------------------------------------------

#include "my_math.hpp"

//--------------------------------------------------


bool double_equal (double first, double second) {

    if (fabs (first - second) < EPSILON) return true;


    return false;
}


size_t my_max (size_t value1, size_t value2) {

    if (value1 > value2) return value1;


    return value2;
}

double my_min (double value1, double value2) {

    if (value1 < value2) return value1;


    return value2;
}

