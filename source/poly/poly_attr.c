#include "internal.h"
#include "poly_mem.h"

/*****************************************************************************/

size_t poly_deg(poly_srcptr op)
{
    return deg(op);
}

void poly_coeff(ring_ptr rop, poly_srcptr op, size_t index)
{
    size_t deg = deg(op);

    if (index > deg)
        ring_set_zero(rop);
    else
        ring_set(rop, coeffs(op)[index]);
}

void poly_set_coeff(poly_ptr rop, ring_srcptr op, size_t index)
{
    if (index >= alloc(rop))
        poly_realloc(rop, index + 1);
    ring_set(coeffs(rop)[index], op);

    poly_normalise(rop);
}

/*****************************************************************************/