#ifndef NTHEORY_RING_R_H
#define NTHEORY_RING_R_H

#include "object.h"

#include <mpfr.h>

/*****************************************************************************/

// Virtual table for R (ring of mpfr floating numbers).
extern const struct ring_vt r_ring[1];

// C struct of R elements.
struct r_ring_vt
{
    struct ring_vt base;
    mpfr_t val;
};

// C type of R elements.
typedef struct r_ring_vt r_ring_t[1];
// C type of R pointers.
typedef struct r_ring_vt *r_ring_ptr;
// C type of R source pointers.
typedef const struct r_ring_vt *r_ring_srcptr;

/*****************************************************************************/

#endif
