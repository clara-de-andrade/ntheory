#ifndef NTHEORY_RING_Z_H
#define NTHEORY_RING_Z_H

#include "object.h"

#include <gmp.h>

/*****************************************************************************/

// Virtual table for Z (ring of mpz integers).
extern const struct ring_vt z_ring[1];

// C struct of Z elements.
struct z_ring_vt
{
    struct ring_vt base;
    mpz_t val;
};

// C type of Z elements.
typedef struct z_ring_vt z_ring_t[1];
// C type of Z pointers.
typedef struct z_ring_vt *z_ring_ptr;
// C type of Z source pointers.
typedef const struct z_ring_vt *z_ring_srcptr;

/*****************************************************************************/

#endif
