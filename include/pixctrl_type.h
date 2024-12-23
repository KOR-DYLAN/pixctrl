#ifndef PIXCTRL_TYPE_H
#define PIXCTRL_TYPE_H

#ifdef  __cplusplus
extern "C" {
#endif

typedef enum {
    PIXCTRL_SUCCESS,
    PIXCTRL_FAILURE,
    PIXCTRL_MUST_NOT_BE_NULL,
    PIXCTRL_MEMORY_ALLOCATION_IS_FAILED,
    PIXCTRL_INVALID_ARGUMENT,
} pixctrl_result_t;

typedef struct {
    uint32_t ir;
    uint32_t ig;
    uint32_t ib;
    uint32_t ia;
    int32_t bpp;
} pixctrl_order_t;

#ifdef  __cplusplus
}
#endif

#endif  /* !PIXCTRL_TYPE_H */
