#include "rings/poly.h"

#include <stdlib.h>

/* ************************************************************************* */

// Evaluates to maximum of two numbers, a and b.
#define max(a, b) ((a) >= (b) ? (a) : (b))
// Evaluates to minimum of two numbers, a and b.
#define min(a, b) ((a) <= (b) ? (a) : (b))

/*****************************************************************************/

#define base(ptr, type) (((type)(ptr))->base)
#define val(ptr, type) (((type)(ptr))->val)

#define ring(ptr) (((poly_ptr)(ptr))->ring)
#define deg(ptr) (((poly_ptr)(ptr))->deg)
#define coeffs(ptr) (((poly_ptr)(ptr))->coeffs)
#define alloc(ptr) (((poly_ptr)(ptr))->alloc)

/* ************************************************************************* */

#define GUARD_NULL_PTR(ptr, type) \
    do                            \
        if (ptr == (type)NULL)    \
        {                         \
            exit(EXIT_FAILURE);   \
        }                         \
    while (0)

/*****************************************************************************/

// Initialises guard for poly_t aliasing (when an operand is passed as `rop`).
#define POLY_GUARD_INIT(ptr, scratch, rop, cond) \
    int _aliased_##scratch = (cond);             \
    poly_t scratch;                              \
    poly_ptr ptr = (rop);                        \
    if (_aliased_##scratch)                      \
    {                                            \
        poly_init(scratch);                      \
        ptr = scratch;                           \
    }

// Clears guard for poly_t aliasing (when an operand is passed as `rop`).
#define POLY_GUARD_CLEAR(rop, scratch) \
    if (_aliased_##scratch)            \
    {                                  \
        poly_set((rop), scratch);      \
        poly_clear(scratch);           \
    }

/* ************************************************************************* */