#ifndef NTHEORY_RING_Q_H
#define NTHEORY_RING_Q_H

#include "object.h"

#include <gmp.h>

/*****************************************************************************/

// Virtual table for Q (ring of mpz rationals).
extern const struct ring_vt q_ring[1];

// C struct of Q elements.
struct q_ring_vt
{
    struct ring_vt base;
    mpq_t val;
};

// C type of Q elements.
typedef struct q_ring_vt q_ring_t[1];
// C type of Q pointers.
typedef struct q_ring_vt *q_ring_ptr;
// C type of Q source pointers.
typedef const struct q_ring_vt *q_ring_srcptr;

/*****************************************************************************/

#endif
