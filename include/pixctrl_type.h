/* 
 * pixctrl - a low level pixel control library
 *
 * MIT License
 * 
 * Copyright (c) 2025 JunKi(Dylan) Hong
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
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
    PIXCTRL_INVALID_RANGE,
    PIXCTRL_INVALID_ARGUMENT,
} pixctrl_result_t;

typedef struct {
    int32_t bpp;
    int32_t ir;
    int32_t ig;
    int32_t ib;
    int32_t ia;
} pixctrl_order_t;

/* 
 - Init 'pixctrl_order_t' data list 
                                   b
                                   p  i  i  i  i
                                   p  r  g  b  a */
#define INIT_PIXCTRL_ORDER_RGBA  { 4, 0, 1, 2, 3, }
#define INIT_PIXCTRL_ORDER_BGRA  { 4, 2, 1, 0, 3, }
#define INIT_PIXCTRL_ORDER_ARGB  { 4, 1, 2, 3, 0, }
#define INIT_PIXCTRL_ORDER_ABGR  { 4, 3, 2, 1, 0, }
#define INIT_PIXCTRL_ORDER_RGB   { 3, 0, 1, 2, 0, }
#define INIT_PIXCTRL_ORDER_BGR   { 3, 2, 1, 0, 0, }

typedef enum {
    /* ARGB32 */
    PIXCTRL_FMT_RGBA32,
    PIXCTRL_FMT_BGRA32,
    PIXCTRL_FMT_ARGB32,
    PIXCTRL_FMT_ABGR32,
    /* XRGB32 */
    PIXCTRL_FMT_RGBX32,
    PIXCTRL_FMT_BGRX32,
    PIXCTRL_FMT_XRGB32,
    PIXCTRL_FMT_XBGR32,
    /* RGB24 */
    PIXCTRL_FMT_BGR24,
    PIXCTRL_FMT_RGB24,
} pixctrl_fmt_t;

#ifdef  __cplusplus
}
#endif

#endif  /* !PIXCTRL_TYPE_H */
