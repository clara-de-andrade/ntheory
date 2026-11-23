#ifndef NTHEORY_POLY_H
#define NTHEORY_POLY_H

#include "rings/object.h"

#include <mpfr.h>

/*****************************************************************************/

// Virtual table for rings of polynomials.
extern const struct ring_vt poly_ring[1];

// C type of polynomial pointers.
typedef struct poly_vt *poly_ptr;
// C type of polynomial source pointers.
typedef const struct poly_vt *poly_srcptr;

/*****************************************************************************/

// C struct of polynomials over a ring.
struct poly_vt
{
    struct ring_vt base;

    ring_srcptr ring;
    size_t deg;

    ring_ptr *coeffs;
    size_t alloc;
};

// C type of polynomials over a ring.
typedef struct poly_vt poly_t[1];

/*****************************************************************************/

size_t poly_deg(poly_srcptr op);
void poly_coeff(ring_ptr rop, poly_srcptr op, size_t index);
void poly_set_coeff(poly_ptr rop, ring_srcptr op, size_t index);

/*****************************************************************************/

void poly_d(poly_ptr rop, poly_srcptr op1);
void poly_eval(ring_ptr rop, poly_srcptr op1, ring_srcptr op2);
void poly_root(mpfr_ptr rop, poly_srcptr op1, mpfr_srcptr op2);

/*****************************************************************************/

#endif
