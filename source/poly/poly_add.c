#include "internal.h"
#include "poly_mem.h"
#include "poly_add.h"

/*****************************************************************************/

void poly_add(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    size_t deg = max(deg(op1), deg(op2));
    poly_set_deg(rop, deg);

    for (size_t i = 0; i <= deg; i++)
        if (i <= deg(op1) && i <= deg(op2))
            ring_add(coeffs(rop)[i], coeffs(op1)[i], coeffs(op2)[i]);
        else if (i <= deg(op1))
            ring_set(coeffs(rop)[i], coeffs(op1)[i]);
        else
            ring_set(coeffs(rop)[i], coeffs(op2)[i]);

    poly_normalise(rop);
}

void poly_sub(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    size_t deg = max(deg(op1), deg(op2));
    poly_set_deg(rop, deg);

    for (size_t i = 0; i <= deg; i++)
        if (i <= deg(op1) && i <= deg(op2))
            ring_sub(coeffs(rop)[i], coeffs(op1)[i], coeffs(op2)[i]);
        else if (i <= deg(op1))
            ring_set(coeffs(rop)[i], coeffs(op1)[i]);
        else
            ring_neg(coeffs(rop)[i], coeffs(op2)[i]);

    poly_normalise(rop);
}

void poly_neg(ring_ptr rop, ring_srcptr op)
{
    size_t deg = deg(op);
    poly_set_deg(rop, deg);

    for (size_t i = 0; i <= deg; i++)
        ring_neg(coeffs(rop)[i], coeffs(op)[i]);
}

/*****************************************************************************/