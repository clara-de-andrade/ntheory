#include "internal.h"
#include "poly_mem.h"
#include "poly_init.h"

/*****************************************************************************/

void poly_init(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_ptr);

    base(rop, poly_ptr) = poly_ring[0];

    coeffs(rop) = malloc(sizeof(ring_ptr));
    GUARD_NULL_PTR(coeffs(rop), ring_ptr *);

    alloc(rop) = 1;
}

void poly_new(ring_ptr rop, va_list ap)
{
    GUARD_NULL_PTR(rop, ring_ptr);

    ring_srcptr ring = va_arg(ap, ring_srcptr);
    ring(rop) = ring;

    size_t deg = va_arg(ap, size_t);
    deg(rop) = deg;
    poly_realloc((poly_ptr)rop, deg + 1);

    ring_ptr coeff;
    for (size_t i = 0; i <= deg; i++)
    {
        coeff = va_arg(ap, ring_srcptr);
        ring_set(coeffs(rop)[i], coeff);
    }

    poly_normalise((poly_ptr)rop);
}

void poly_set(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    GUARD_NULL_PTR(op, ring_srcptr);

    size_t deg = deg(op);
    poly_set_deg((poly_ptr)rop, deg);

    ring_srcptr ring = ring(op);
    poly_set_ring((poly_ptr)rop, ring);

    for (size_t i = 0; i <= deg; i++)
        poly_set_coeff((poly_ptr)rop, coeffs(op)[i], i);
}

void poly_clear(ring_ptr rop)
{
    if (coeffs(rop) == (ring_ptr *)NULL)
        goto end;

    for (size_t i = 0; i < alloc(rop); i++)
        ring_clear(coeffs(rop)[i]);
    free(coeffs(rop));

end:
    ring(rop) = (ring_srcptr)NULL;
    alloc(rop) = 0;
    deg(rop) = 0;
}

/*****************************************************************************/