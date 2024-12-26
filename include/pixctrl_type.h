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
    PIXCTRL_NOT_SUPPORT,
    PIXCTRL_MUST_NOT_BE_NULL,
    PIXCTRL_MEMORY_ALLOCATION_IS_FAILED,
    PIXCTRL_INVALID_RANGE,
    PIXCTRL_INVALID_ARGUMENT,
} pixctrl_result_t;

typedef struct {
    int32_t bpp;    /* bytes-per-pixel */
    int32_t ir;     /* red   index */
    int32_t ig;     /* green index */
    int32_t ib;     /* blue  index */
    int32_t ia;     /* alpha index */
} pixctrl_rgb_order_t;

typedef struct {
    int32_t bpp;    /* bytes-per-pixel */
    int32_t iy;     /* Y index */
    int32_t iu;     /* U index */
    int32_t iv;     /* V index */
    int32_t ia;     /* alpha index */
} pixctrl_yuv_order_t;

/* 
 - Init RGB 'pixctrl_order_t' data list 
                                      b
                                      p  i  i  i  i
                                      p  r  g  b  a */
#define INIT_PIXCTRL_ORDER_RGBA     { 4, 0, 1, 2, 3, }
#define INIT_PIXCTRL_ORDER_BGRA     { 4, 2, 1, 0, 3, }
#define INIT_PIXCTRL_ORDER_ARGB     { 4, 1, 2, 3, 0, }
#define INIT_PIXCTRL_ORDER_ABGR     { 4, 3, 2, 1, 0, }
#define INIT_PIXCTRL_ORDER_RGB      { 3, 0, 1, 2, 0, }
#define INIT_PIXCTRL_ORDER_BGR      { 3, 2, 1, 0, 0, }

/* 
 - Init YUV Interleaved 'pixctrl_order_t' data list 
                                      b
                                      p  i  i  i  i
                                      p  y  u  v  a */
#define INIT_PIXCTRL_ORDER_YUV444   { 3, 0, 1, 2, 0, }
#define INIT_PIXCTRL_ORDER_YUYV422  { 2, 0, 1, 3, 0, }
#define INIT_PIXCTRL_ORDER_YVYU422  { 2, 2, 3, 1, 0, }
#define INIT_PIXCTRL_ORDER_UYVY422  { 2, 1, 0, 2, 0, }
#define INIT_PIXCTRL_ORDER_VYUY422  { 2, 1, 2, 0, 0, }
#define INIT_PIXCTRL_ORDER_NV12     { 2, 0, 0, 1, 0, }
#define INIT_PIXCTRL_ORDER_NV21     { 2, 0, 1, 0, 0, }


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
    /* YUV444 */
    PIXCTRL_FMT_YUV444,
    PIXCTRL_FMT_YUV444P,
    /* YUV422 */
    PIXCTRL_FMT_YUYV422,
    PIXCTRL_FMT_YVYU422,
    PIXCTRL_FMT_UYVY422,
    PIXCTRL_FMT_VYUY422,
    PIXCTRL_FMT_YUV422P,
    /* YUV420 */
    PIXCTRL_FMT_NV12,
    PIXCTRL_FMT_NV21,
    PIXCTRL_FMT_YUV420P,
} pixctrl_fmt_t;

#ifdef  __cplusplus
}
#endif

#endif  /* !PIXCTRL_TYPE_H */
