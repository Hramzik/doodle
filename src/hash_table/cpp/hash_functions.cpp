

//--------------------------------------------------


#include "../hpp/hash_table.hpp"


//--------------------------------------------------


int hf_constant_one (const char* value) {

    (void) value;


    return 1;
}


int hf_first_char (const char* value) {

    return *value;
}


int hf_strlen (const char* value) {

    int len = 0;

    while (*value != '\0') {

        len += 1;

        value += 1;
    }


    return len;
}


int hf_sum_char (const char* value) {

    int sum = 0;

    while (*value != '\0') {

        sum += *value;

        value += 1;
    }


    return sum;
}


int hf_rorxor (const char* value) {

    int hash = 0;
    int lowest_bit = 0;

    while (*value != '\0') {

        hash ^= *value;

        lowest_bit = hash & 1;
        hash  = hash >> 1;
        hash |= (lowest_bit << (INT_SIZE * 8 - 1));


        value += 1;
    }


    return hash;
}


int hf_rolxor (const char* value) {

    int hash = 0;
    int highest_bit = 0;

    while (*value != '\0') {

        hash ^= *value;

        highest_bit = hash & (1 << (INT_SIZE * 8 - 1));
        hash = hash << 1;
        hash |= highest_bit >> (INT_SIZE * 8 - 1);


        value += 1;
    }


    return hash;
}


int hf_crc32 (const char* value) {

    int crc_table[256];
    int crc; int i, j;

    for (i = 0; i < 256; i++) {

        crc = i;

        for (j = 0; j < 8; j++) {

            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        }

        crc_table [i] = crc;
    };


    crc = 0xFFFFFFFFUL;

    while (*value != '\0') {

        crc = crc_table [(crc ^ *value++) & 0xFF] ^ (crc >> 8);
    }


    return crc ^ 0xFFFFFFFFUL;
}


inline int hf_crc32_opt (const char* value) {

    int hash = -1;

    while (*value != '\0') {

        hash = _mm_crc32_u8 (hash, *value);

        value += 1;
    }


    return hash;
}


inline int hf_crc32_opt_2 (const char* value) {

    int hash = -1;


    asm volatile (

        ".intel_syntax noprefix\n"

        "crc32_opt_2_next_byte:\n"
        "mov ch, [rbx]\n"
        "cmp ch, 0\n"
        "je crc32_opt_2_exit\n"

        "crc32 eax, ch\n"
        "inc rbx\n"
        "jmp crc32_opt_2_next_byte\n"

        "crc32_opt_2_exit:\n"

        ".att_syntax prefix\n"
        : "=a" (hash)
        : "a"  (hash), "b" (value)
        : "rcx"
    );


    return hash;
}

