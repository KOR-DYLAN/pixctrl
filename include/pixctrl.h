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
extern void pixctrl_generic_rgb_to_rgb_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                   uint8_t *dst, const pixctrl_rgb_order_t *dst_order,
                                                   int32_t width);
extern void pixctrl_generic_argb_to_argb_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                     uint8_t *dst, const pixctrl_rgb_order_t *dst_order,
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

/********************************************************************************************
 *  RGB to YUV Converter
 ********************************************************************************************
 */
/* Interleaved Line-Stripe Function */
extern void pixctrl_generic_rgb_to_yuv444_interleaved_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                                  uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                                  int32_t width);
extern void pixctrl_generic_rgb_to_yuv422_interleaved_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                                  uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                                  int32_t width);
extern void pixctrl_generic_rgb_to_yuv420_interleaved_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                                  uint8_t *y_dst, uint8_t *uv_dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                                  int32_t width, int32_t row);

/* Planar Line-Stripe Function */
extern void pixctrl_generic_rgb_to_yuv444_planar_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                             uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                             int32_t width);
extern void pixctrl_generic_rgb_to_yuv422_planar_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                             uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                             int32_t width);
extern void pixctrl_generic_rgb_to_yuv420_planar_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                             uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                             int32_t width, int32_t row);

/* rgb to Interleaved yuv444 */
extern pixctrl_result_t pixctrl_generic_rgb_to_yuv444_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr_to_yuv444_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_yuv444_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_yuv444_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_yuv444_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_yuv444_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* rgb to Interleaved yuyv422 */
extern pixctrl_result_t pixctrl_generic_rgb_to_yuyv422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr_to_yuyv422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_yuyv422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_yuyv422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_yuyv422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_yuyv422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* rgb to Interleaved yvyu422 */
extern pixctrl_result_t pixctrl_generic_rgb_to_yvyu422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr_to_yvyu422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_yvyu422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_yvyu422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_yvyu422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_yvyu422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* rgb to Interleaved uyvy422 */
extern pixctrl_result_t pixctrl_generic_rgb_to_uyvy422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr_to_uyvy422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_uyvy422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_uyvy422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_uyvy422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_uyvy422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* rgb to Interleaved vyuy422 */
extern pixctrl_result_t pixctrl_generic_rgb_to_vyuy422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr_to_vyuy422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_vyuy422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_vyuy422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_vyuy422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_vyuy422_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* rgb to Interleaved nv12 */
extern pixctrl_result_t pixctrl_generic_rgb_to_nv12_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr_to_nv12_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_nv12_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_nv12_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_nv12_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_nv12_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* rgb to Interleaved nv21 */
extern pixctrl_result_t pixctrl_generic_rgb_to_nv21_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr_to_nv21_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_nv21_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_nv21_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_nv21_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_nv21_interleaved(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* rgb to Planar yuv444 */
extern pixctrl_result_t pixctrl_generic_rgb_to_yuv444_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr_to_yuv444_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_yuv444_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_yuv444_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_yuv444_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_yuv444_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* rgb to Planar yuv422 */
extern pixctrl_result_t pixctrl_generic_rgb_to_yuv422_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr_to_yuv422_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_yuv422_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_yuv422_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_yuv422_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_yuv422_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* rgb to Planar yuv420 */
extern pixctrl_result_t pixctrl_generic_rgb_to_yuv420_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr_to_yuv420_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_yuv420_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_yuv420_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_yuv420_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_yuv420_planar(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

#ifdef  __cplusplus
}
#endif

#endif /* !PIXCTRL_H */
