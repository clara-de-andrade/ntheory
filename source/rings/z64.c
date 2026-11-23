#include "internal.h"

#include "rings/z64.h"

/*****************************************************************************/

static void z64_init(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    base(rop, z64_ring_ptr) = z64_ring[0];
}

static void z64_new(ring_ptr rop, va_list ap)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z64_ring)
        exit(EXIT_FAILURE);

    val(rop, z64_ring_ptr) = va_arg(ap, long long);
}

static void z64_set(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z64_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != z64_ring)
        exit(EXIT_FAILURE);

    val(rop, z64_ring_ptr) = (val(op, z64_ring_ptr));
}

static void z64_clear(ring_ptr rop)
{
    return;
}

/*****************************************************************************/

static void z64_add(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z64_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != z64_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != z64_ring)
        exit(EXIT_FAILURE);

    val(rop, z64_ring_ptr) = val(op1, z64_ring_ptr) + val(op2, z64_ring_ptr);
}

static void z64_sub(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z64_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != z64_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != z64_ring)
        exit(EXIT_FAILURE);

    val(rop, z64_ring_ptr) = val(op1, z64_ring_ptr) - val(op2, z64_ring_ptr);
}

static void z64_neg(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z64_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != z64_ring)
        exit(EXIT_FAILURE);

    val(rop, z64_ring_ptr) = -val(op, z64_ring_ptr);
}

static void z64_mul(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z64_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != z64_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != z64_ring)
        exit(EXIT_FAILURE);

    val(rop, z64_ring_ptr) = val(op1, z64_ring_ptr) * val(op2, z64_ring_ptr);
}

/*****************************************************************************/

static int z64_is_zero(ring_srcptr op)
{
    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != z64_ring)
        exit(EXIT_FAILURE);

    return (val(op, z64_ring_ptr) == 0);
}

static void z64_set_zero(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z64_ring)
        exit(EXIT_FAILURE);

    val(rop, z64_ring_ptr) = 0;
}

static int z64_is_one(ring_srcptr op)
{
    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != z64_ring)
        exit(EXIT_FAILURE);

    return (val(op, z64_ring_ptr) == 1);
}

static void z64_set_one(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z64_ring)
        exit(EXIT_FAILURE);

    val(rop, z64_ring_ptr) = 1;
}

static int z64_eq(ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != z64_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != z64_ring)
        exit(EXIT_FAILURE);

    return (val(op1, z64_ring_ptr) == val(op2, z64_ring_ptr));
}

/*****************************************************************************/

static int z64_cmp(ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != z64_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != z64_ring)
        exit(EXIT_FAILURE);

    if (val(op1, z64_ring_ptr) > val(op2, z64_ring_ptr))
        return +1;
    else if (val(op1, z64_ring_ptr) < val(op2, z64_ring_ptr))
        return -1;
    else
        return 0;
}

/*****************************************************************************/

const struct ring_vt z64_ring[1] = {{
    .vt = z64_ring,
    .size = sizeof(z64_ring_t),

    .init = z64_init,
    .set = z64_set,
    .new_ = z64_new,
    .clear = z64_clear,

    .add = z64_add,
    .sub = z64_sub,
    .neg = z64_neg,
    .mul = z64_mul,
    .lmul = z64_mul,

    .is_zero = z64_is_zero,
    .set_zero = z64_set_zero,
    .is_one = z64_is_one,
    .set_one = z64_set_one,
    .eq = z64_eq,

    .cmp = z64_cmp,
}};

/*****************************************************************************/
