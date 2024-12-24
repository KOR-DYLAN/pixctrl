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
#ifndef PIXCTRL_H
#define PIXCTRL_H

#include <stddef.h>
#include <stdint.h>
#include "pixctrl_type.h"

#ifdef  __cplusplus
extern "C" {
#endif

/********************************************************************************************
 *  Util
 ********************************************************************************************
 */
extern size_t pixctrl_get_image_size(pixctrl_fmt_t fmt, int32_t width, int32_t height);
extern const char *pixctrl_get_format_as_ffmpeg_style_string(pixctrl_fmt_t fmt);

/********************************************************************************************
 *  RGB to RGB Converter
 ********************************************************************************************
 */
/* Line-Stripe Function */
extern void pixctrl_generic_rgb_to_rgb_line_stripe(uint8_t *src, const pixctrl_order_t *src_order,
                                                   uint8_t *dst, const pixctrl_order_t *dst_order,
                                                   int32_t width);
extern void pixctrl_generic_argb_to_argb_line_stripe(uint8_t *src, const pixctrl_order_t *src_order,
                                                     uint8_t *dst, const pixctrl_order_t *dst_order,
                                                     int32_t width);

/* xxxa to xxx Function */
extern pixctrl_result_t pixctrl_generic_rgba_to_rgb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_bgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_rgb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_bgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* axxx to xxx Function */
extern pixctrl_result_t pixctrl_generic_argb_to_rgb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_bgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_rgb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_bgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* xxxa to xxxa Function */
extern pixctrl_result_t pixctrl_generic_rgba_to_bgra(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_rgba(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* xxxa to axxx Function */
extern pixctrl_result_t pixctrl_generic_rgba_to_abgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_argb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* axxx to xxxa Function */
extern pixctrl_result_t pixctrl_generic_argb_to_bgra(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_rgba(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* axxx to axxx Function */
extern pixctrl_result_t pixctrl_generic_argb_to_abgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_argb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* xxx to xxx Function */
extern pixctrl_result_t pixctrl_generic_rgb_to_bgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr_to_rgb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

#ifdef  __cplusplus
}
#endif

#endif /* !PIXCTRL_H */
