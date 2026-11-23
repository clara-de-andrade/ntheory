#include "rings/poly.h"

/* ************************************************************************* */

void poly_set_ring(poly_ptr rop, ring_srcptr op);
void poly_realloc(poly_ptr rop, size_t alloc);
void poly_set_deg(poly_ptr rop, size_t deg);
void poly_normalise(poly_t rop);

/* ************************************************************************* */