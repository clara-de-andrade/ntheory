#include "internal.h"

/*****************************************************************************/

void ring_init(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(op, ring_srcptr);
    GUARD_NULL_PTR(op->init, ring_fun_t);

    op->init(rop);
}

void ring_new(ring_ptr rop, ...)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    GUARD_NULL_PTR(rop->new_, ring_var_t);

    va_list ap;
    va_start(ap, rop);

    rop->new_(rop, ap);

    va_end(ap);
}

void ring_set(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(op, ring_ptr);
    GUARD_NULL_PTR(op->set, ring_op_t);

    if (rop == op)
        return;
    op->set(rop, op);
}

void ring_clear(ring_ptr rop)
{
    if (rop == (ring_ptr)NULL)
        return;

    GUARD_NULL_PTR(rop->clear, ring_fun_t);

    rop->clear(rop);
}

/*****************************************************************************/

void ring_add(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    RING_GUARD_INIT(ptr, scratch, rop, rop == op1 || rop == op2);
    GUARD_NULL_PTR(ptr, ring_ptr);
    GUARD_NULL_PTR(ptr->add, ring_op2_t);

    ptr->add(ptr, op1, op2);

    RING_GUARD_CLEAR(rop, scratch);
}

void ring_sub(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    RING_GUARD_INIT(ptr, scratch, rop, rop == op1 || rop == op2);
    GUARD_NULL_PTR(ptr, ring_ptr);
    GUARD_NULL_PTR(ptr->sub, ring_op2_t);

    ptr->sub(ptr, op1, op2);

    RING_GUARD_CLEAR(rop, scratch);
}

void ring_neg(ring_ptr rop, ring_srcptr op)
{
    RING_GUARD_INIT(ptr, scratch, rop, rop == op);
    GUARD_NULL_PTR(ptr, ring_ptr);
    GUARD_NULL_PTR(ptr->neg, ring_op_t);

    ptr->neg(ptr, op);

    RING_GUARD_CLEAR(rop, scratch);
}

void ring_mul(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    RING_GUARD_INIT(ptr, scratch, rop, rop == op1 || rop == op2);
    GUARD_NULL_PTR(ptr, ring_ptr);
    GUARD_NULL_PTR(ptr->mul, ring_op2_t);

    ptr->mul(ptr, op1, op2);

    RING_GUARD_CLEAR(rop, scratch);
}

void ring_lmul(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    RING_GUARD_INIT(ptr, scratch, rop, rop == op1 || rop == op2);
    GUARD_NULL_PTR(ptr, ring_ptr);
    GUARD_NULL_PTR(ptr->lmul, ring_op2_t);

    ptr->lmul(ptr, op1, op2);

    RING_GUARD_CLEAR(rop, scratch);
}

void ring_pow(ring_ptr rop, ring_srcptr op1, int64_t op2)
{
    RING_GUARD_INIT(ptr, scratch, rop, rop == op1);
    GUARD_NULL_PTR(ptr, ring_ptr);

    if (ptr->pow != (ring_pow_t)NULL)
    {
        ptr->pow(ptr, op1, op2);

        RING_GUARD_CLEAR(rop, scratch);
        return;
    }

    ring_set_one(ptr);
    if (op2 == 0)
    {
        RING_GUARD_CLEAR(rop, scratch);
        return;
    }

    if (op2 == 1)
    {
        ring_set(ptr, op1);

        RING_GUARD_CLEAR(rop, scratch);
        return;
    }

    if (ring_is_zero(op1))
    {
        ring_set_zero(ptr);

        RING_GUARD_CLEAR(rop, scratch);
        return;
    }

    if (ring_is_one(op1))
    {
        RING_GUARD_CLEAR(rop, scratch);
        return;
    }

    RING_TEMP_INIT(base, op1);
    ring_set(base, op1);
    while (op2 > 0)
    {
        if (op2 & 1)
            ring_mul(ptr, ptr, base);
        op2 >>= 1;
        if (op2 > 0)
            ring_mul(base, base, base);
    }
    ring_clear(base);

    RING_GUARD_CLEAR(rop, scratch);
}

/*****************************************************************************/

int ring_is_zero(ring_srcptr op)
{
    GUARD_NULL_PTR(op, ring_srcptr);
    GUARD_NULL_PTR(op->is_zero, ring_pred_t);

    return op->is_zero(op);
}

void ring_set_zero(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    GUARD_NULL_PTR(rop->set_zero, ring_fun_t);

    rop->set_zero(rop);
}

int ring_is_one(ring_srcptr op)
{
    GUARD_NULL_PTR(op, ring_srcptr);
    GUARD_NULL_PTR(op->is_one, ring_pred_t);

    return op->is_one(op);
}

void ring_set_one(ring_ptr rop)
{
    GUARD_NULL_PTR(rop, ring_ptr);
    GUARD_NULL_PTR(rop->set_one, ring_fun_t);

    rop->set_one(rop);
}

int ring_eq(ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(op1, ring_srcptr);

    if (op1->eq != (ring_rel_t)NULL)
        return op1->eq(op1, op2);
    else if (op1->cmp != (ring_rel_t)NULL)
        return (op1->cmp(op1, op2) == 0);
    else
        exit(EXIT_FAILURE);
}

/*****************************************************************************/

int ring_cmp(ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(op1, ring_srcptr);
    GUARD_NULL_PTR(op1->cmp, ring_rel_t);

    return op1->cmp(op1, op2);
}

/*****************************************************************************/

void ring_inv(ring_ptr rop, ring_srcptr op)
{
    GUARD_NULL_PTR(op, ring_srcptr);
    GUARD_NULL_PTR(op->inv, ring_op_t);

    op->inv(rop, op);
}

void ring_div(ring_ptr rop, ring_srcptr op1, ring_srcptr op2)
{
    GUARD_NULL_PTR(op1, ring_srcptr);
    GUARD_NULL_PTR(op1->inv, ring_op_t);

    op1->div(rop, op1, op2);
}

/*****************************************************************************/

void ring_sum(ring_ptr rop, ...)
{
    RING_TEMP_INIT(acc, rop);
    ring_set_zero(acc);

    va_list ap;
    va_start(ap, rop);

    ring_srcptr op;
    while (1)
    {
        op = va_arg(ap, ring_srcptr);
        if (op == (ring_srcptr)NULL)
            break;
        ring_add(acc, acc, op);
    }

    va_end(ap);

    ring_set(rop, acc);
    ring_clear(acc);
}

void ring_prod(ring_ptr rop, ...)
{
    RING_TEMP_INIT(acc, rop);
    ring_set_one(acc);

    va_list ap;
    va_start(ap, rop);

    ring_srcptr op;
    while (1)
    {
        op = va_arg(ap, ring_srcptr);
        if (op == (ring_srcptr)NULL)
            break;
        ring_mul(acc, acc, op);
    }

    va_end(ap);

    ring_set(rop, acc);
    ring_clear(acc);
}

void ring_ma(ring_ptr rop, ring_srcptr op1, ring_srcptr op2, ring_srcptr op3)
{
    RING_GUARD_INIT(ptr, scratch, rop, rop == op1 || rop == op2 || rop == op3);

    ring_mul(ptr, op1, op2);
    ring_add(ptr, ptr, op3);

    RING_GUARD_CLEAR(rop, scratch);
}

void ring_lma(ring_ptr rop, ring_srcptr op1, ring_srcptr op2, ring_srcptr op3)
{
    RING_GUARD_INIT(ptr, scratch, rop, rop == op1 || rop == op2 || rop == op3);

    ring_lmul(ptr, op1, op2);
    ring_add(ptr, ptr, op3);

    RING_GUARD_CLEAR(rop, scratch);
}

/*****************************************************************************/