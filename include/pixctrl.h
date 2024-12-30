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
/* Interleaved to Interleaved Line-Stripe Function */
extern void pixctrl_generic_xrgb_to_rgb24_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                      uint8_t *dst, const pixctrl_rgb_order_t *dst_order,
                                                      int32_t width);
extern void pixctrl_generic_xrgb32_to_argb32_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                     uint8_t *dst, const pixctrl_rgb_order_t *dst_order,
                                                     int32_t width);

/* Interleaved to Planar Line-Stripe Function */
/* Planar to Interleaved Line-Stripe Function */
/* Planar to Planar Line-Stripe Function */

/* Interleaved xxxa to Interleaved xxx Function */
extern pixctrl_result_t pixctrl_generic_rgba_to_rgb24(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_bgr24(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_rgb24(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_bgr24(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved axxx to Interleaved xxx Function */
extern pixctrl_result_t pixctrl_generic_argb_to_rgb24(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_bgr24(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_rgb24(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_bgr24(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved xxxa to Interleaved xxxa Function */
extern pixctrl_result_t pixctrl_generic_rgba_to_bgra(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_rgba(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved xxxa to Interleaved axxx Function */
extern pixctrl_result_t pixctrl_generic_rgba_to_abgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_argb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved axxx to Interleaved xxxa Function */
extern pixctrl_result_t pixctrl_generic_argb_to_bgra(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_rgba(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved axxx to Interleaved axxx Function */
extern pixctrl_result_t pixctrl_generic_argb_to_abgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_argb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved xxx to Interleaved xxx Function */
extern pixctrl_result_t pixctrl_generic_rgb24_to_bgr24(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr24_to_rgb24(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/********************************************************************************************
 *  RGB to YUV Converter
 ********************************************************************************************
 */
/* Interleaved to Interleaved Line-Stripe Function */
extern void pixctrl_generic_xrgb_to_yuv444_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                                  uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                                  int32_t width);
extern void pixctrl_generic_xrgb_to_yuv422_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                                  uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                                  int32_t width);
extern void pixctrl_generic_xrgb_to_yuv420_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                                  uint8_t *y_dst, uint8_t *uv_dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                                  int32_t width, int32_t row);

/* Interleaved to Planar Line-Stripe Function */
extern void pixctrl_generic_xrgb_to_yuv444p_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                             uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                             int32_t width);
extern void pixctrl_generic_xrgb_to_yuv422p_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                             uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                             int32_t width);
extern void pixctrl_generic_xrgb_to_yuv420p_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                             uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                             int32_t width, int32_t row);

/* Planar to Interleaved Line-Stripe Function */
/* Planar to Planar Line-Stripe Function */

/* Interleaved rgb to Interleaved yuv444 */
extern pixctrl_result_t pixctrl_generic_rgb24_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr24_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved rgb to Interleaved yuyv422 */
extern pixctrl_result_t pixctrl_generic_rgb24_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr24_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved rgb to Interleaved yvyu422 */
extern pixctrl_result_t pixctrl_generic_rgb24_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr24_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved rgb to Interleaved uyvy422 */
extern pixctrl_result_t pixctrl_generic_rgb24_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr24_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved rgb to Interleaved vyuy422 */
extern pixctrl_result_t pixctrl_generic_rgb24_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr24_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved rgb to Interleaved nv12 */
extern pixctrl_result_t pixctrl_generic_rgb24_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr24_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved rgb to Interleaved nv21 */
extern pixctrl_result_t pixctrl_generic_rgb24_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr24_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved rgb to Planar yuv444 */
extern pixctrl_result_t pixctrl_generic_rgb24_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr24_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved rgb to Planar yuv422 */
extern pixctrl_result_t pixctrl_generic_rgb24_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr24_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved rgb to Planar yuv420 */
extern pixctrl_result_t pixctrl_generic_rgb24_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgr24_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_argb_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_abgr_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_rgba_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_bgra_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/********************************************************************************************
 *  YUV to YUV Converter
 ********************************************************************************************
 */
/* Interleaved to Interleaved Line-Stripe Function */
extern void pixctrl_generic_yuv444_to_yuv422_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                         uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                         int32_t width);
extern void pixctrl_generic_yuv444_to_yuv420_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                         uint8_t *y_dst, uint8_t *uv_dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                         int32_t width, int32_t row);

extern void pixctrl_generic_yuv422_to_yuv444_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *uv_src_order,
                                                         uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                         int32_t width);
extern void pixctrl_generic_yuv422_to_yuv420_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *uv_src_order,
                                                         uint8_t *y_dst, uint8_t *uv_dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                         int32_t width, int32_t row);

extern void pixctrl_generic_yuv420_to_yuv444_line_stripe(uint8_t *y_src, uint8_t *uv_src, const pixctrl_yuv_order_t *uv_src_order,
                                                         uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                         int32_t width);
extern void pixctrl_generic_yuv420_to_yuv422_line_stripe(uint8_t *y_src, uint8_t *uv_src, const pixctrl_yuv_order_t *uv_src_order,
                                                         uint8_t *dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                         int32_t width);

/* Interleaved to Planar Line-Stripe Function */
extern void pixctrl_generic_yuv444_to_yuv444p_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                          uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                          int32_t width);
extern void pixctrl_generic_yuv444_to_yuv422p_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                          uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                          int32_t width);
extern void pixctrl_generic_yuv444_to_yuv420p_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                          uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                          int32_t width, int32_t row);

extern void pixctrl_generic_yuv422_to_yuv444p_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                          uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                          int32_t width);
extern void pixctrl_generic_yuv422_to_yuv422p_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                          uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                          int32_t width);
extern void pixctrl_generic_yuv422_to_yuv420p_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                          uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                          int32_t width, int32_t row);

/* Planar to Interleaved Line-Stripe Function */
/* Planar to Planar Line-Stripe Function */

/* Interleaved yuv444 to Interleaved yuv422 */
extern pixctrl_result_t pixctrl_generic_yuv444_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yuv444_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yuv444_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yuv444_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved yuv444 to Interleaved yuv420 */
extern pixctrl_result_t pixctrl_generic_yuv444_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yuv444_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved yuv422 to Interleaved yuv444 */
extern pixctrl_result_t pixctrl_generic_yuyv422_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yvyu422_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_uyvy422_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_vyuy422_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved yuv422 to Interleaved yuv420 */
extern pixctrl_result_t pixctrl_generic_yuyv422_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yvyu422_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_uyvy422_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_vyuy422_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yuyv422_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yvyu422_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_uyvy422_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_vyuy422_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved yuv420 to Interleaved yuv444 */
extern pixctrl_result_t pixctrl_generic_nv12_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_nv21_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved yuv420 to Interleaved yuv422 */
extern pixctrl_result_t pixctrl_generic_nv12_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_nv12_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_nv12_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_nv12_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_nv21_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_nv21_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_nv21_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_nv21_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved yuv444 to Planar */
extern pixctrl_result_t pixctrl_generic_yuv444_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yuv444_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yuv444_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/* Interleaved yuv422 to Planar */
extern pixctrl_result_t pixctrl_generic_yuyv422_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yvyu422_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_uyvy422_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_vyuy422_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yuyv422_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yvyu422_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_uyvy422_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_vyuy422_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yuyv422_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_yvyu422_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_uyvy422_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);
extern pixctrl_result_t pixctrl_generic_vyuy422_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

/********************************************************************************************
 *  YUV to RGB Converter
 ********************************************************************************************
 */
/* Interleaved to Interleaved Line-Stripe Function */
/* Interleaved to Planar Line-Stripe Function */
/* Planar to Interleaved Line-Stripe Function */
/* Planar to Planar Line-Stripe Function */

#ifdef  __cplusplus
}
#endif

#endif /* !PIXCTRL_H */
