#ifndef ARRAY_STRUCTS_HPP_INCLUDED
#define ARRAY_STRUCTS_HPP_INCLUDED
//--------------------------------------------------


#include <stdio.h>
#include "enums.hpp"


//--------------------------------------------------


typedef struct Array {

    void* buffer;
    size_t size;
    size_t capacity;


    Array_element_type element_type;

} Array; const size_t ARRAY_SIZE = sizeof (Array);


//--------------------------------------------------
#endif