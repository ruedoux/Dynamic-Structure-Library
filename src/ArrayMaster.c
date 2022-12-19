#include "ArrayMaster.h"

// ---------------------------------------
// OVERFLOW MANAGEMENT
// ---------------------------------------

int size_t_will_overflow_minus(size_t a, size_t b)
{
    if (b > 0 && a <= 0 + b) { return 1; }
    return 0;
}

int size_t_will_overflow_add(size_t a, size_t b)
{
    if (b > 0 && a > SIZE_MAX - b) { return 1; }
    return 0;
}
