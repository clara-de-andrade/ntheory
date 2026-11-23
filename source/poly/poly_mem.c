#include "internal.h"
#include "poly_mem.h"

/* ************************************************************************* */

void poly_set_ring(poly_ptr rop, ring_srcptr op)
{
    for (size_t i = 0; i < alloc(rop); i++)
        ring_clear(coeffs(rop)[i]);

    ring(rop) = op;

    for (size_t i = 0; i < alloc(rop); i++)
        ring_init(coeffs(rop)[i], op);
}

void poly_realloc(poly_ptr rop, size_t alloc)
{
    if (alloc <= alloc(rop))
        return;

    size_t max_alloc = SIZE_MAX / sizeof(mpfr_t);

    if (alloc > max_alloc)
        exit(EXIT_FAILURE);

    size_t new_alloc;
    if (alloc(rop) > (max_alloc >> 1))
        new_alloc = max_alloc;
    else
        new_alloc = max(alloc, alloc(rop) << 1);
    mpfr_t *coeffs = realloc(coeffs(rop), new_alloc * sizeof(mpfr_t));

    if (coeffs == (mpfr_t *)NULL)
        exit(EXIT_FAILURE);
    coeffs(rop) = coeffs;

    for (size_t i = alloc(rop); i < new_alloc; i++)
    {
        ring_init(coeffs(rop)[i], ring(rop));
        ring_set_zero(coeffs(rop)[i]);
    }
    alloc(rop) = new_alloc;
}

void poly_set_deg(poly_ptr rop, size_t deg)
{
    if (deg == SIZE_MAX)
        exit(EXIT_FAILURE);

    poly_realloc(rop, deg + 1);

    if (deg < deg(rop))
        for (size_t i = deg + 1; i <= deg(rop); i++)
            ring_set_zero(coeffs(rop)[i]);

    deg(rop) = deg;
}

void poly_normalise(poly_t rop)
{
    while (ring_is_zero(coeffs(rop)[deg(rop)]) && deg(rop) > 0)
        deg(rop)--;
}

/* ************************************************************************* */