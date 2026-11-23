#ifndef NTHEORY_RING_OBJECT_H
#define NTHEORY_RING_OBJECT_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

/*****************************************************************************/

// C type of ring pointers.
typedef struct ring_vt *ring_ptr;
// C type of ring source pointers.
typedef const struct ring_vt *ring_srcptr;

/*****************************************************************************/

// C type of function.
typedef void (*ring_fun_t)(ring_ptr);
// C type of variadic function.
typedef void (*ring_var_t)(ring_ptr, va_list);
// C type of unary operation.
typedef void (*ring_op_t)(ring_ptr, ring_srcptr);
// C type of binary operation.
typedef void (*ring_op2_t)(ring_ptr, ring_srcptr, ring_srcptr);
// C type of predicate.
typedef int (*ring_pred_t)(ring_srcptr);
// C type of relation.
typedef int (*ring_rel_t)(ring_srcptr, ring_srcptr);

// C Type of `pow` method
typedef void (*ring_pow_t)(ring_ptr, ring_srcptr, int64_t);

/*****************************************************************************/

// C struct of ring elements.
struct ring_vt
{
    ring_srcptr vt; // Pointer
    size_t size;    // Size of vt

    ring_fun_t init;  // Initialization
    ring_var_t new_;  // Declaration
    ring_op_t set;    // Assignment
    ring_fun_t clear; // Destruction

    ring_op2_t add;  // Addition
    ring_op2_t sub;  // Subtraction
    ring_op_t neg;   // Negation
    ring_op2_t mul;  // Multiplication
    ring_op2_t lmul; // Scalar multiplication
    ring_pow_t pow;  // Exponentiation

    ring_pred_t is_zero; // Comparison to zero element
    ring_fun_t set_zero; // Assignment to zero element
    ring_pred_t is_one;  // Comparison to unit element
    ring_fun_t set_one;  // Assignment to unit element
    ring_rel_t eq;       // Equality

    ring_rel_t cmp; // Comparison (ordered rings)

    ring_op_t inv;  // Inverse (fields)
    ring_op2_t div; // Division (fields)
};

// C type of ring elements.
typedef struct ring_vt ring_t[1];

/*****************************************************************************/

void ring_init(ring_ptr rop, ring_srcptr op);
void ring_new(ring_ptr rop, ...);
void ring_set(ring_ptr rop, ring_srcptr op);
void ring_clear(ring_ptr rop);

void ring_add(ring_ptr rop, ring_srcptr op1, ring_srcptr op2);
void ring_sub(ring_ptr rop, ring_srcptr op1, ring_srcptr op2);
void ring_neg(ring_ptr rop, ring_srcptr op);
void ring_mul(ring_ptr rop, ring_srcptr op1, ring_srcptr op2);
void ring_lmul(ring_ptr rop, ring_srcptr op1, ring_srcptr op2);
void ring_pow(ring_ptr rop, ring_srcptr op1, int64_t op2);

int ring_is_zero(ring_srcptr op);
int ring_is_one(ring_srcptr op);
void ring_set_zero(ring_ptr rop);
void ring_set_one(ring_ptr rop);
int ring_eq(ring_srcptr op1, ring_srcptr op2);

int ring_cmp(ring_srcptr op1, ring_srcptr op2);
#define ring_gte(op1, op2) (ring_cmp(op1, op2) >= 0)
#define ring_gt(op1, op2) (ring_cmp(op1, op2) > 0)
#define ring_lte(op1, op2) (ring_cmp(op1, op2) <= 0)
#define ring_lt(op1, op2) (ring_cmp(op1, op2) < 0)

void ring_inv(ring_ptr rop, ring_srcptr op);
void ring_div(ring_ptr rop, ring_srcptr op1, ring_srcptr op2);

/*****************************************************************************/

void ring_sum(ring_ptr rop, ...);
void ring_prod(ring_ptr rop, ...);

void ring_ma(ring_ptr rop, ring_srcptr op1, ring_srcptr op2, ring_srcptr op3);
void ring_lma(ring_ptr rop, ring_srcptr op1, ring_srcptr op2, ring_srcptr op3);

/*****************************************************************************/

#endif
