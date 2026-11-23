#ifndef NTHEORY_RING_Z64_H
#define NTHEORY_RING_Z64_H

#include "object.h"

#include <stdint.h>

/*****************************************************************************/

// Virtual table for Z/2**64Z (ring of C integers).
extern const struct ring_vt z64_ring[1];

// C struct of Z/2**64Z elements.
struct z64_ring_vt
{
    struct ring_vt base;
    int64_t val;
};

// C type of Z/2**64Z elements.
typedef struct z64_ring_vt z64_ring_t[1];
// C type of Z/2**64Z pointers.
typedef struct z64_ring_vt *z64_ring_ptr;
// C type of Z/2**64Z source pointers.
typedef const struct z64_ring_vt *z64_ring_srcptr;

/*****************************************************************************/

#endif
