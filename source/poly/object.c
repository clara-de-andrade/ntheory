#include "internal.h"
#include "poly_init.h"
#include "poly_add.h"

/*****************************************************************************/

const struct ring_vt poly_ring[1] = {{
    .vt = poly_ring,
    .size = sizeof(poly_t),

    .init = poly_init,
    .set = poly_set,
    .new_ = poly_new,
    .clear = poly_clear,

    .add = poly_add,
    .sub = poly_sub,
    .neg = poly_neg,
}};

/*****************************************************************************/
