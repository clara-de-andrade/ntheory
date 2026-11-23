#include "internal.h"

#include "rings/z64.h"
#include "rings/z.h"

/*****************************************************************************/

static void z_init(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    base(rop, z_ring_ptr) = z_ring[0];
    mpz_init(val(rop, z_ring_ptr));
}

static void z_new(ring_ptr rop, va_list ap)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z_ring)
        exit(EXIT_FAILURE);

    mpz_srcptr z = va_arg(ap, mpz_srcptr);
    mpz_set(val(rop, z_ring_ptr), z);
}

static void z_set(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != z_ring)
        exit(EXIT_FAILURE);

    mpz_set(val(rop, z_ring_ptr), (val(op, z_ring_ptr)));
}

static void z_clear(ring_ptr op)
{
    mpz_clear(val(op, z_ring_ptr));
}

/*****************************************************************************/

static void z_add(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != z_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != z_ring)
        exit(EXIT_FAILURE);

    mpz_add(val(rop, z_ring_ptr), val(op1, z_ring_ptr), val(op2, z_ring_ptr));
}

static void z_sub(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != z_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != z_ring)
        exit(EXIT_FAILURE);

    mpz_sub(val(rop, z_ring_ptr), val(op1, z_ring_ptr), val(op2, z_ring_ptr));
}

static void z_neg(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != z_ring)
        exit(EXIT_FAILURE);

    mpz_neg(val(rop, z_ring_ptr), val(op, z_ring_ptr));
}

static void z_mul(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != z_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != z_ring)
        exit(EXIT_FAILURE);

    mpz_mul(val(rop, z_ring_ptr), val(op1, z_ring_ptr), val(op2, z_ring_ptr));
}

static void z_lmul(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != z_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);

    if (op2->vt == z64_ring)
        mpz_mul_si(val(rop, z_ring_ptr),
                   val(op1, z_ring_ptr), val(op2, z64_ring_ptr));
    else
        exit(EXIT_FAILURE);
}

/*****************************************************************************/

static int z_is_zero(ring_srcptr op)
{
    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != z_ring)
        exit(EXIT_FAILURE);

    return (mpz_cmp_ui(val(op, z_ring_ptr), 0) == 0);
}

static void z_set_zero(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z_ring)
        exit(EXIT_FAILURE);

    mpz_set_ui(val(rop, z_ring_ptr), 0);
}

static int z_is_one(ring_srcptr op)
{
    GUARD_NULL_PTR(op, ring_srcptr);
    if (op->vt != z_ring)
        exit(EXIT_FAILURE);

    return (mpz_cmp_ui(val(op, z_ring_ptr), 1) == 0);
}

static void z_set_one(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    if (rop->vt != z_ring)
        exit(EXIT_FAILURE);

    mpz_set_ui(val(rop, z_ring_ptr), 1);
}

/*****************************************************************************/

static int z_cmp(ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(op1, ring_srcptr);
    if (op1->vt != z_ring)
        exit(EXIT_FAILURE);

    GUARD_NULL_PTR(op2, ring_srcptr);
    if (op2->vt != z_ring)
        exit(EXIT_FAILURE);

    return mpz_cmp(val(op1, z_ring_ptr), val(op2, z_ring_ptr));
}

/*****************************************************************************/

const struct ring_vt z_ring[1] = {{
    .vt = z_ring,
    .size = sizeof(z_ring_t),

    .init = z_init,
    .set = z_set,
    .new_ = z_new,
    .clear = z_clear,

    .add = z_add,
    .sub = z_sub,
    .neg = z_neg,
    .mul = z_mul,
    .lmul = z_lmul,

    .is_zero = z_is_zero,
    .set_zero = z_set_zero,
    .is_one = z_is_one,
    .set_one = z_set_one,

    .cmp = z_cmp,
}};

/*****************************************************************************/
