#include "internal.h"

#include "rings/z64.h"
#include "rings/z.h"
#include "rings/q.h"

/*****************************************************************************/

static void q_init(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    base(rop, z_ring_ptr) = q_ring[0];
    mpq_init(val(rop, q_ring_ptr));
}

static void q_new(ring_ptr rop, va_list ap)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != q_ring)
        exit(EXIT_FAILURE);

    mpq_srcptr q = va_arg(ap, mpq_srcptr);
    mpq_set(val(rop, q_ring_ptr), q);
}

static void q_set(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != q_ring)
        exit(EXIT_FAILURE);

    mpq_set(val(rop, q_ring_ptr), (val(op, q_ring_ptr)));
}

static void q_clear(ring_ptr op)
{
    mpq_clear(val(op, q_ring_ptr));
}

/*****************************************************************************/

static void q_add(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != q_ring)
        exit(EXIT_FAILURE);

    mpq_add(val(rop, q_ring_ptr), val(op1, q_ring_ptr), val(op2, q_ring_ptr));
}

static void q_sub(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != q_ring)
        exit(EXIT_FAILURE);

    mpq_sub(val(rop, q_ring_ptr), val(op1, q_ring_ptr), val(op2, q_ring_ptr));
}

static void q_neg(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != q_ring)
        exit(EXIT_FAILURE);

    mpq_neg(val(rop, q_ring_ptr), val(op, q_ring_ptr));
}

static void q_mul(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != q_ring)
        exit(EXIT_FAILURE);

    mpq_mul(val(rop, q_ring_ptr), val(op1, q_ring_ptr), val(op2, q_ring_ptr));
}

static void q_lmul(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);

    if (op2->vt == z64_ring)
    {
        mpq_t q_op2;
        mpq_init(q_op2);
        mpq_set_si(q_op2, val(op2, z64_ring_ptr), 1);

        mpq_mul(val(rop, q_ring_ptr), val(op1, q_ring_ptr), q_op2);

        mpq_clear(q_op2);
    }
    else if (op2->vt == z_ring)
    {
        mpq_t q_op2;
        mpq_init(q_op2);
        mpq_set_z(q_op2, val(op2, z_ring_ptr));

        mpq_mul(val(rop, q_ring_ptr), val(op1, q_ring_ptr), q_op2);

        mpq_clear(q_op2);
    }
    else
        exit(EXIT_FAILURE);
}

/*****************************************************************************/

static int q_is_zero(ring_srcptr op)
{
    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != q_ring)
        exit(EXIT_FAILURE);

    return (mpq_cmp_ui(val(op, q_ring_ptr), 0, 1) == 0);
}

static void q_set_zero(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != q_ring)
        exit(EXIT_FAILURE);

    mpq_set_ui(val(rop, q_ring_ptr), 0, 1);
}

static int q_is_one(ring_srcptr op)
{
    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != q_ring)
        exit(EXIT_FAILURE);

    return (mpq_cmp_ui(val(op, q_ring_ptr), 1, 1) == 0);
}

static void q_set_one(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != q_ring)
        exit(EXIT_FAILURE);

    mpq_set_ui(val(rop, q_ring_ptr), 1, 1);
}

/*****************************************************************************/

static int q_cmp(ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != q_ring)
        exit(EXIT_FAILURE);

    return mpq_cmp(val(op1, q_ring_ptr), val(op2, q_ring_ptr));
}

/*****************************************************************************/

static void q_inv(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != q_ring)
        exit(EXIT_FAILURE);

    mpq_inv(val(rop, q_ring_ptr), val(op, q_ring_ptr));
}

static void q_div(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != q_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != q_ring)
        exit(EXIT_FAILURE);

    mpq_div(val(rop, q_ring_ptr), val(op1, q_ring_ptr), val(op2, q_ring_ptr));
}

/*****************************************************************************/

const struct ring_vt q_ring[1] = {{
    .vt = q_ring,
    .size = sizeof(q_ring_t),

    .init = q_init,
    .set = q_set,
    .new_ = q_new,
    .clear = q_clear,

    .add = q_add,
    .sub = q_sub,
    .neg = q_neg,
    .mul = q_mul,
    .lmul = q_lmul,

    .is_zero = q_is_zero,
    .set_zero = q_set_zero,
    .is_one = q_is_one,
    .set_one = q_set_one,

    .cmp = q_cmp,
    .inv = q_inv,
    .div = q_div,
}};

/*****************************************************************************/
