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
#include <stdlib.h>
#include "pixctrl.h"
#include "common/util.h"

/********************************************************************************************
 *  Core Function
 ********************************************************************************************
 */
static inline pixctrl_result_t pixctrl_generic_core_xrgb_to_yuv444(const pixctrl_rgb_order_t src_order, 
                                                                   uint8_t *src, uint8_t *dst, 
                                                                   int32_t width, int32_t height)
{
    const pixctrl_yuv_order_t dst_order = INIT_PIXCTRL_ORDER_YUV444;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_xrgb_to_yuv444_line_stripe(src_row_base, &src_order, 
                                                                  dst_row_base, &dst_order, 
                                                                  width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_xrgb_to_yuv422(const pixctrl_rgb_order_t src_order, 
                                                                   const pixctrl_yuv_order_t dst_order, 
                                                                   uint8_t *src, uint8_t *dst, 
                                                                   int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if ((width % 2) == 0)
        {
            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_xrgb_to_yuv422_line_stripe(src_row_base, &src_order, 
                                                                      dst_row_base, &dst_order, 
                                                                      width);
                src_row_base += src_stride;
                dst_row_base += dst_stride;
            }
        }
        else
        {
            result = PIXCTRL_INVALID_RANGE;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_xrgb_to_yuv420(const pixctrl_rgb_order_t src_order, 
                                                                   const pixctrl_yuv_order_t dst_order, 
                                                                   uint8_t *src, uint8_t *dst, 
                                                                   int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src;
    uint8_t *y_dst_row_base = dst, *uv_dst_row_base = NULL;
    register int32_t src_stride = width * src_order.bpp;
    register int32_t y_stride = width;
    register int32_t uv_stride = width * (dst_order.bpp / 2);
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            uv_dst_row_base = y_dst_row_base + (y_stride * height);
            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_xrgb_to_yuv420_line_stripe(src_row_base, &src_order, 
                                                                      y_dst_row_base, uv_dst_row_base, &dst_order, 
                                                                      width, row);
                src_row_base += src_stride;
                y_dst_row_base += y_stride;
                if((row % 2) != 0)
                {
                    uv_dst_row_base += uv_stride;
                }
            }
        }
        else
        {
            result = PIXCTRL_INVALID_RANGE;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_xrgb_to_yuv444p(const pixctrl_rgb_order_t src_order, 
                                                                    uint8_t *src, uint8_t *dst, 
                                                                    int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src;
    uint8_t *y_dst_row_base = NULL;
    uint8_t *u_dst_row_base = NULL;
    uint8_t *v_dst_row_base = NULL;
    register int32_t src_stride = width * src_order.bpp;
    register int32_t yuv_stride = width;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        y_dst_row_base = dst;
        u_dst_row_base = y_dst_row_base + (yuv_stride * height);
        v_dst_row_base = u_dst_row_base + (yuv_stride * height);

        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_xrgb_to_yuv444p_line_stripe(src_row_base, &src_order, 
                                                             y_dst_row_base, u_dst_row_base, v_dst_row_base, 
                                                             width);
            src_row_base += src_stride;
            y_dst_row_base += yuv_stride;
            u_dst_row_base += yuv_stride;
            v_dst_row_base += yuv_stride;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_xrgb_to_yuv422p(const pixctrl_rgb_order_t src_order, 
                                                                    uint8_t *src, uint8_t *dst, 
                                                                    int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src;
    uint8_t *y_dst_row_base = NULL;
    uint8_t *u_dst_row_base = NULL;
    uint8_t *v_dst_row_base = NULL;
    register int32_t src_stride = width * src_order.bpp;
    register int32_t y_stride = width;
    register int32_t uv_stride = width / 2;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if ((width % 2) == 0)
        {
            y_dst_row_base = dst;
            u_dst_row_base = y_dst_row_base + (y_stride * height);
            v_dst_row_base = u_dst_row_base + (uv_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_xrgb_to_yuv422p_line_stripe(src_row_base, &src_order, 
                                                                 y_dst_row_base, u_dst_row_base, v_dst_row_base, 
                                                                 width);
                src_row_base += src_stride;
                y_dst_row_base += y_stride;
                u_dst_row_base += uv_stride;
                v_dst_row_base += uv_stride;
            }
        }
        else
        {
            result = PIXCTRL_INVALID_RANGE;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_xrgb_to_yuv420p(const pixctrl_rgb_order_t src_order, 
                                                                    uint8_t *src, uint8_t *dst, 
                                                                    int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src;
    uint8_t *y_dst_row_base = NULL;
    uint8_t *u_dst_row_base = NULL;
    uint8_t *v_dst_row_base = NULL;
    register int32_t src_stride = width * src_order.bpp;
    register int32_t y_stride = width;
    register int32_t uv_stride = width / 2;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            y_dst_row_base = dst;
            u_dst_row_base = y_dst_row_base + (y_stride * height);
            v_dst_row_base = u_dst_row_base + (uv_stride * (height / 2));

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_xrgb_to_yuv420p_line_stripe(src_row_base, &src_order, 
                                                                 y_dst_row_base, u_dst_row_base, v_dst_row_base, 
                                                                 width, row);
                src_row_base += src_stride;
                y_dst_row_base += y_stride;
                if((row % 2) != 0)
                {
                    u_dst_row_base += uv_stride;
                    v_dst_row_base += uv_stride;
                }
            }
        }
        else
        {
            result = PIXCTRL_INVALID_RANGE;
        }
    }

    return result;
}

/********************************************************************************************
 *  rgb to Interleaved yuv444
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_rgb24_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv444((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGB, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgr24_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv444((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGR, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_argb_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv444((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ARGB, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_abgr_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv444((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ABGR, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_rgba_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv444((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGBA, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgra_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv444((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGRA, src, dst, width, height);
}

/********************************************************************************************
 *  rgb to Interleaved yuv422
 ********************************************************************************************
 */
/* rgb to Interleaved yuyv422 */
pixctrl_result_t pixctrl_generic_rgb24_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGB, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgr24_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGR, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_argb_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ARGB, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_abgr_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ABGR, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_rgba_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGBA, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgra_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGRA, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                               src, dst, width, height);
}

/* rgb to Interleaved yvyu422 */
pixctrl_result_t pixctrl_generic_rgb24_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGB, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgr24_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGR, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_argb_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ARGB, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_abgr_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ABGR, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_rgba_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGBA, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgra_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGRA, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                               src, dst, width, height);
}

/* rgb to Interleaved uyvy422 */
pixctrl_result_t pixctrl_generic_rgb24_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGB, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgr24_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGR, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_argb_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ARGB, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_abgr_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ABGR, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_rgba_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGBA, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgra_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGRA, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                               src, dst, width, height);
}

/* rgb to Interleaved vyuy422 */
pixctrl_result_t pixctrl_generic_rgb24_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGB, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgr24_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGR, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_argb_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ARGB, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_abgr_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ABGR, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_rgba_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGBA, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgra_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGRA, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                               src, dst, width, height);
}


/********************************************************************************************
 *  rgb to Interleaved yuv420
 ********************************************************************************************
 */
/* rgb to Interleaved nv12 */
pixctrl_result_t pixctrl_generic_rgb24_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGB, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgr24_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGR, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_argb_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ARGB, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_abgr_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ABGR, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_rgba_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGBA, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgra_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGRA, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                               src, dst, width, height);
}

/* rgb to Interleaved nv21 */
pixctrl_result_t pixctrl_generic_rgb24_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGB, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgr24_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGR, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_argb_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ARGB, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_abgr_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ABGR, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_rgba_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGBA, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                               src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgra_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGRA, 
                                               (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                               src, dst, width, height);
}

/********************************************************************************************
 *  rgb to Planar yuv444
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_rgb24_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv444p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGB, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgr24_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv444p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGR, src, dst, width, height);
}
pixctrl_result_t pixctrl_generic_argb_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv444p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ARGB, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_abgr_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv444p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ABGR, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_rgba_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv444p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGBA, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgra_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv444p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGRA, src, dst, width, height);
}

/********************************************************************************************
 *  rgb to Planar yuv422
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_rgb24_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGB, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgr24_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGR, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_argb_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ARGB, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_abgr_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ABGR, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_rgba_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGBA, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgra_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv422p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGRA, src, dst, width, height);
}

/********************************************************************************************
 *  rgb to Planar yuv420
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_rgb24_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGB, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgr24_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGR, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_argb_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ARGB, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_abgr_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_ABGR, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_rgba_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_RGBA, src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_bgra_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_xrgb_to_yuv420p((const pixctrl_rgb_order_t)INIT_PIXCTRL_ORDER_BGRA, src, dst, width, height);
}
