#include "internal.h"
#include "poly_mem.h"

/*****************************************************************************/

void poly_d(poly_ptr rop, poly_srcptr op1);
void poly_eval(ring_ptr rop, poly_srcptr op1, ring_ptr op2);
void poly_root(mpfr_ptr rop, poly_srcptr op1, mpfr_srcptr op2);

/*****************************************************************************/