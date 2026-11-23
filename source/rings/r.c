#include "internal.h"

#include "rings/z64.h"
#include "rings/z.h"
#include "rings/q.h"
#include "rings/r.h"

/*****************************************************************************/

static void r_init(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_srcptr);
    base(rop, r_ring_ptr) = r_ring[0];
    mpfr_init(val(rop, r_ring_ptr));
}

static void r_new(ring_ptr rop, va_list ap)
{
    GUARD_NULL_PTR(rop, ring_srcptr);
    if (rop->vt != r_ring)
        exit(EXIT_FAILURE);

    mpfr_srcptr x = va_arg(ap, mpfr_srcptr);
    mpfr_set(val(rop, r_ring_ptr), x, MPFR_RNDN);
}

static void r_set(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(rop, ring_srcptr);
    if (rop->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != r_ring)
        exit(EXIT_FAILURE);

    mpfr_set(val(rop, r_ring_ptr), (val(op, r_ring_ptr)), MPFR_RNDN);
    ;
}

static void r_clear(ring_ptr op)
{
    mpfr_clear(val(op, r_ring_ptr));
}

/*****************************************************************************/

static void r_add(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_srcptr);
    if (rop->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != r_ring)
        exit(EXIT_FAILURE);

    mpfr_add(val(rop, r_ring_ptr), val(op1, r_ring_ptr), val(op2, r_ring_ptr), MPFR_RNDN);
}

static void r_sub(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_srcptr);
    if (rop->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != r_ring)
        exit(EXIT_FAILURE);

    mpfr_sub(val(rop, r_ring_ptr), val(op1, r_ring_ptr), val(op2, r_ring_ptr), MPFR_RNDN);
}

static void r_neg(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(rop, ring_srcptr);
    if (rop->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != r_ring)
        exit(EXIT_FAILURE);

    mpfr_neg(val(rop, r_ring_ptr), val(op, r_ring_ptr), MPFR_RNDN);
}

static void r_mul(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_srcptr);
    if (rop->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != r_ring)
        exit(EXIT_FAILURE);

    mpfr_mul(val(rop, r_ring_ptr), val(op1, r_ring_ptr), val(op2, r_ring_ptr), MPFR_RNDN);
}

static void r_lmul(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_srcptr);
    if (rop->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);

    if (op2->vt == z64_ring)
        mpfr_mul_si(val(rop, r_ring_ptr),
                    val(op1, r_ring_ptr), val(op2, z64_ring_ptr), MPFR_RNDN);
    else if (op2->vt == z_ring)
        mpfr_mul_z(val(rop, r_ring_ptr),
                   val(op1, r_ring_ptr), val(op2, z_ring_ptr), MPFR_RNDN);
    else if (op2->vt == q_ring)
        mpfr_mul_q(val(rop, r_ring_ptr),
                   val(op1, r_ring_ptr), val(op2, q_ring_ptr), MPFR_RNDN);
    else
        exit(EXIT_FAILURE);
}

/*****************************************************************************/

static int r_is_zero(ring_srcptr op)
{
    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != r_ring)
        exit(EXIT_FAILURE);

    return mpfr_zero_p(val(op, r_ring_ptr));
}

static void r_set_zero(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_srcptr);
    if (rop->vt != r_ring)
        exit(EXIT_FAILURE);

    mpfr_set_ui(val(rop, r_ring_ptr), 0, MPFR_RNDN);
}

static int r_is_one(ring_srcptr op)
{
    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != r_ring)
        exit(EXIT_FAILURE);

    return (!mpfr_nan_p(val(op, r_ring_ptr)) && mpfr_cmp_ui(val(op, r_ring_ptr), 1) == 0);
}

static void r_set_one(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_srcptr);
    if (rop->vt != r_ring)
        exit(EXIT_FAILURE);

    mpfr_set_ui(val(rop, r_ring_ptr), 1, MPFR_RNDN);
}

/*****************************************************************************/

static int r_cmp(ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != r_ring)
        exit(EXIT_FAILURE);

    return mpfr_cmp(val(op1, r_ring_ptr), val(op2, r_ring_ptr));
}

/*****************************************************************************/

static void r_inv(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(rop, ring_srcptr);
    if (rop->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != r_ring)
        exit(EXIT_FAILURE);

    mpfr_ui_div(val(rop, r_ring_ptr), 1, val(op, r_ring_ptr), MPFR_RNDN);
}

static void r_div(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_srcptr);
    if (rop->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != r_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != r_ring)
        exit(EXIT_FAILURE);

    mpfr_div(val(rop, r_ring_ptr), val(op1, r_ring_ptr), val(op2, r_ring_ptr), MPFR_RNDN);
}

/*****************************************************************************/

const struct ring_vt r_ring[1] = {{
    .vt = r_ring,
    .size = sizeof(r_ring_t),

    .init = r_init,
    .set = r_set,
    .new_ = r_new,
    .clear = r_clear,

    .add = r_add,
    .sub = r_sub,
    .neg = r_neg,
    .mul = r_mul,
    .lmul = r_lmul,

    .is_zero = r_is_zero,
    .set_zero = r_set_zero,
    .is_one = r_is_one,
    .set_one = r_set_one,

    .cmp = r_cmp,
    .inv = r_inv,
    .div = r_div,
}};

/*****************************************************************************/
