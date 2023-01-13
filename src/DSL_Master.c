#include "DSL_Master.h"

// ---------------------------------------
// OVERFLOW MANAGEMENT
// ---------------------------------------

bool size_t_will_underflow(size_t a, size_t b)
{
    if (b > 0 && a <= 0 + b) { return true; }
    return false;
}

bool size_t_will_overflow(size_t a, size_t b)
{
    if (b > 0 && a > SIZE_MAX - b) { return true; }
    return false;
}
