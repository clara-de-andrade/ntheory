#include "rings/object.h"

#include <stdalign.h>
#include <stddef.h>
#include <stdlib.h>

/*****************************************************************************/

#define base(ptr, type) (((type)(ptr))->base)
#define val(ptr, type) (((type)(ptr))->val)

/*****************************************************************************/

#define GUARD_NULL_PTR(ptr, type) \
    do                            \
        if (ptr == (type)NULL)    \
        {                         \
            exit(EXIT_FAILURE);   \
        }                         \
    while (0)

/*****************************************************************************/

#define RING_BUFFER_DECLARE(var, bytes)                     \
    alignas(max_align_t) unsigned char _buf_##var[(bytes)]; \
    ring_ptr var = (ring_ptr)_buf_##var

/*****************************************************************************/

#define RING_TEMP_INIT(var, model)           \
    GUARD_NULL_PTR(model, ring_srcptr);      \
    RING_BUFFER_DECLARE(var, (model)->size); \
    ring_init(var, (model))

#define RING_GUARD_INIT(ptr, scratch, rop, cond)                        \
    int _aliased_##scratch = (cond);                                    \
    RING_BUFFER_DECLARE(scratch, _aliased_##scratch ? (rop)->size : 1); \
    ring_ptr ptr = (rop);                                               \
    if (_aliased_##scratch)                                             \
    {                                                                   \
        ring_init(scratch, rop);                                        \
        ptr = scratch;                                                  \
    }

#define RING_GUARD_CLEAR(rop, scratch) \
    if (_aliased_##scratch)            \
    {                                  \
        ring_set((rop), scratch);      \
        ring_clear(scratch);           \
    }

/*****************************************************************************/