#ifndef HASH_TABLE_ENUMS_INCLUDED
#define HASH_TABLE_ENUMS_INCLUDED
//--------------------------------------------------


enum Hash_function {

    HF_CONSTANT_ONE,
    HF_FIRST_CHAR,
    HF_STRLEN,
    HF_SUM_CHAR,
    HF_RORXOR,
    HF_ROLXOR,
    HF_CRC32,
    HF_CRC32_OPT,
    HF_CRC32_OPT_2,
    //HF_CRC32_OPT_3,
};


//--------------------------------------------------
#endif