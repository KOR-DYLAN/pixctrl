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
static inline pixctrl_result_t pixctrl_generic_core_yuv444_to_yuv422(const pixctrl_yuv_order_t src_order, 
                                                                     const pixctrl_yuv_order_t dst_order, 
                                                                     uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0))
        {
            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv444_to_yuv422_line_stripe(src_row_base, &src_order, 
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

static inline pixctrl_result_t pixctrl_generic_core_yuv444_to_yuv420(const pixctrl_yuv_order_t src_order, 
                                                                     const pixctrl_yuv_order_t dst_order, 
                                                                     uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src;
    uint8_t *y_dst_row_base = dst;
    uint8_t *uv_dst_row_base = NULL;
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
                pixctrl_generic_yuv444_to_yuv420_line_stripe(src_row_base, &src_order, 
                                                                         y_dst_row_base, uv_dst_row_base, &dst_order, 
                                                                         width, row);
                src_row_base += src_stride;
                y_dst_row_base += y_stride;
                if ((row % 2) != 0)
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

static inline pixctrl_result_t pixctrl_generic_core_yuv422_to_yuv444(const pixctrl_yuv_order_t src_order, 
                                                                     const pixctrl_yuv_order_t dst_order, 
                                                                     uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0))
        {
            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv422_to_yuv444_line_stripe(src_row_base, &src_order, 
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

static inline pixctrl_result_t pixctrl_generic_core_yuv422_to_yuv420(const pixctrl_yuv_order_t src_order, 
                                                                     const pixctrl_yuv_order_t dst_order, 
                                                                     uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src;
    uint8_t *y_dst_row_base = dst;
    uint8_t *uv_dst_row_base = NULL;
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
                pixctrl_generic_yuv422_to_yuv420_line_stripe(src_row_base, &src_order, 
                                                             y_dst_row_base, uv_dst_row_base, &dst_order, 
                                                             width, row);
                src_row_base += src_stride;
                y_dst_row_base += y_stride;
                if ((row % 2) != 0)
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

static inline pixctrl_result_t pixctrl_generic_core_yuv420_to_yuv444(const pixctrl_yuv_order_t src_order, 
                                                                     const pixctrl_yuv_order_t dst_order, 
                                                                     uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = src;
    uint8_t *uv_src_row_base = NULL;
    uint8_t *dst_row_base = dst;
    register int32_t y_stride = width;
    register int32_t uv_stride = width * (src_order.bpp / 2);
    register int32_t dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            uv_src_row_base = y_src_row_base + (y_stride * height);
            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv420_to_yuv444_line_stripe(y_src_row_base, uv_src_row_base, &src_order, 
                                                             dst_row_base, &dst_order, 
                                                             width);
                y_src_row_base += y_stride;
                dst_row_base += dst_stride;
                if ((row % 2) != 0)
                {
                    uv_src_row_base += uv_stride;
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

static inline pixctrl_result_t pixctrl_generic_core_yuv420_to_yuv422(const pixctrl_yuv_order_t src_order, 
                                                                     const pixctrl_yuv_order_t dst_order, 
                                                                     uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = src;
    uint8_t *uv_src_row_base = NULL;
    uint8_t *dst_row_base = dst;
    register int32_t y_stride = width;
    register int32_t uv_stride = width * (src_order.bpp / 2);
    register int32_t dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            uv_src_row_base = y_src_row_base + (y_stride * height);
            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv420_to_yuv422_line_stripe(y_src_row_base, uv_src_row_base, &src_order, 
                                                             dst_row_base, &dst_order, 
                                                             width);
                y_src_row_base += y_stride;
                dst_row_base += dst_stride;
                if ((row % 2) != 0)
                {
                    uv_src_row_base += uv_stride;
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

static inline pixctrl_result_t pixctrl_generic_core_yuv444_to_yuv444p(const pixctrl_yuv_order_t src_order,
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
            pixctrl_generic_yuv444_to_yuv444p_line_stripe(src_row_base, &src_order, 
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

static inline pixctrl_result_t pixctrl_generic_core_yuv444_to_yuv422p(const pixctrl_yuv_order_t src_order,
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
    register int32_t uv_stride = width >> 1;    /* == (width / 2) */
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
                pixctrl_generic_yuv444_to_yuv422p_line_stripe(src_row_base, &src_order, 
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

static inline pixctrl_result_t pixctrl_generic_core_yuv444_to_yuv420p(const pixctrl_yuv_order_t src_order,
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
    register int32_t uv_stride = width >> 1;    /* == (width / 2) */
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
                pixctrl_generic_yuv444_to_yuv420p_line_stripe(src_row_base, &src_order, 
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

static inline pixctrl_result_t pixctrl_generic_core_yuv422_to_yuv444p(const pixctrl_yuv_order_t src_order,
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
        if ((width % 2) == 0)
        {
            y_dst_row_base = dst;
            u_dst_row_base = y_dst_row_base + (yuv_stride * height);
            v_dst_row_base = u_dst_row_base + (yuv_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv422_to_yuv444p_line_stripe(src_row_base, &src_order, 
                                                              y_dst_row_base, u_dst_row_base, v_dst_row_base,
                                                              width);
                src_row_base += src_stride;
                y_dst_row_base += yuv_stride;
                u_dst_row_base += yuv_stride;
                v_dst_row_base += yuv_stride;
            }
        }
        else
        {
            result = PIXCTRL_INVALID_RANGE;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_yuv422_to_yuv422p(const pixctrl_yuv_order_t src_order,
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
    register int32_t uv_stride = width >> 1;    /* == (width / 2) */
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
                pixctrl_generic_yuv422_to_yuv422p_line_stripe(src_row_base, &src_order, 
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

static inline pixctrl_result_t pixctrl_generic_core_yuv422_to_yuv420p(const pixctrl_yuv_order_t src_order,
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
    register int32_t uv_stride = width >> 1;    /* == (width / 2) */
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
                pixctrl_generic_yuv422_to_yuv420p_line_stripe(src_row_base, &src_order, 
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

static inline pixctrl_result_t pixctrl_generic_core_yuv420_to_yuv444p(const pixctrl_yuv_order_t src_order,
                                                                      uint8_t *src, uint8_t *dst, 
                                                                      int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = NULL;
    uint8_t *uv_src_row_base = NULL;
    uint8_t *y_dst_row_base = NULL;
    uint8_t *u_dst_row_base = NULL;
    uint8_t *v_dst_row_base = NULL;
    register int32_t yuv_stride = width;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            y_src_row_base = src;
            uv_src_row_base = y_src_row_base + (yuv_stride * height);

            y_dst_row_base = dst;
            u_dst_row_base = y_dst_row_base + (yuv_stride * height);
            v_dst_row_base = u_dst_row_base + (yuv_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv420_to_yuv444p_line_stripe(y_src_row_base, uv_src_row_base, &src_order, 
                                                              y_dst_row_base, u_dst_row_base, v_dst_row_base,
                                                              width);

                y_src_row_base += yuv_stride;
                if((row % 2) != 0)
                {
                    uv_src_row_base += yuv_stride;
                }

                y_dst_row_base += yuv_stride;
                u_dst_row_base += yuv_stride;
                v_dst_row_base += yuv_stride;
            }
        }
        else
        {
            result = PIXCTRL_INVALID_RANGE;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_yuv420_to_yuv422p(const pixctrl_yuv_order_t src_order,
                                                                      uint8_t *src, uint8_t *dst, 
                                                                      int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = NULL;
    uint8_t *uv_src_row_base = NULL;
    uint8_t *y_dst_row_base = NULL;
    uint8_t *u_dst_row_base = NULL;
    uint8_t *v_dst_row_base = NULL;
    register int32_t yuv_stride = width;
    register int32_t y_stride = width;
    register int32_t uv_stride = width >> 1;    /* == (width / 2) */
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            y_src_row_base = src;
            uv_src_row_base = y_src_row_base + (yuv_stride * height);

            y_dst_row_base = dst;
            u_dst_row_base = y_dst_row_base + (y_stride * height);
            v_dst_row_base = u_dst_row_base + (uv_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv420_to_yuv422p_line_stripe(y_src_row_base, uv_src_row_base, &src_order, 
                                                              y_dst_row_base, u_dst_row_base, v_dst_row_base,
                                                              width);

                y_src_row_base += yuv_stride;
                if((row % 2) != 0)
                {
                    uv_src_row_base += yuv_stride;
                }

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

static inline pixctrl_result_t pixctrl_generic_core_yuv420_to_yuv420p(const pixctrl_yuv_order_t src_order,
                                                                      uint8_t *src, uint8_t *dst, 
                                                                      int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = NULL;
    uint8_t *uv_src_row_base = NULL;
    uint8_t *y_dst_row_base = NULL;
    uint8_t *u_dst_row_base = NULL;
    uint8_t *v_dst_row_base = NULL;
    register int32_t yuv_stride = width;
    register int32_t y_stride = width;
    register int32_t uv_stride = width >> 1;    /* == (width / 2) */
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            y_src_row_base = src;
            uv_src_row_base = y_src_row_base + (yuv_stride * height);

            y_dst_row_base = dst;
            u_dst_row_base = y_dst_row_base + (y_stride * height);
            v_dst_row_base = u_dst_row_base + (uv_stride * (height / 2));

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv420_to_yuv420p_line_stripe(y_src_row_base, uv_src_row_base, &src_order, 
                                                              y_dst_row_base, u_dst_row_base, v_dst_row_base,
                                                              width, row);

                y_src_row_base += yuv_stride;
                y_dst_row_base += y_stride;
                if((row % 2) != 0)
                {
                    uv_src_row_base += yuv_stride;
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

static inline pixctrl_result_t pixctrl_generic_core_yuv444p_to_yuv444(const pixctrl_yuv_order_t dst_order,
                                                                      uint8_t *src, uint8_t *dst, 
                                                                      int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = NULL;
    uint8_t *u_src_row_base = NULL;
    uint8_t *v_src_row_base = NULL;
    uint8_t *dst_row_base = dst;
    register int32_t src_stride = width;
    register int32_t dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        y_src_row_base = src;
        u_src_row_base = y_src_row_base + (src_stride * height);
        v_src_row_base = u_src_row_base + (src_stride * height);

        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_yuv444p_to_yuv444_line_stripe(y_src_row_base, u_src_row_base, v_src_row_base,
                                                          dst_row_base, &dst_order,
                                                          width);

            y_src_row_base += src_stride;
            u_src_row_base += src_stride;
            v_src_row_base += src_stride;
            
            dst_row_base += dst_stride;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_yuv444p_to_yuv422(const pixctrl_yuv_order_t dst_order,
                                                                      uint8_t *src, uint8_t *dst, 
                                                                      int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = NULL;
    uint8_t *u_src_row_base = NULL;
    uint8_t *v_src_row_base = NULL;
    uint8_t *dst_row_base = dst;
    register int32_t src_stride = width;
    register int32_t dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if ((width % 2) == 0)
        {
            y_src_row_base = src;
            u_src_row_base = y_src_row_base + (src_stride * height);
            v_src_row_base = u_src_row_base + (src_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv444p_to_yuv422_line_stripe(y_src_row_base, u_src_row_base, v_src_row_base,
                                                            dst_row_base, &dst_order,
                                                            width);

                y_src_row_base += src_stride;
                u_src_row_base += src_stride;
                v_src_row_base += src_stride;
                
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

static inline pixctrl_result_t pixctrl_generic_core_yuv444p_to_yuv420(const pixctrl_yuv_order_t dst_order,
                                                                      uint8_t *src, uint8_t *dst, 
                                                                      int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = NULL;
    uint8_t *u_src_row_base = NULL;
    uint8_t *v_src_row_base = NULL;
    uint8_t *y_dst_row_base = NULL;
    uint8_t *uv_dst_row_base = NULL;
    register int32_t src_stride = width;
    register int32_t y_dst_stride = width;
    register int32_t uv_dst_stride = width * (dst_order.bpp / 2);
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            y_src_row_base = src;
            u_src_row_base = y_src_row_base + (src_stride * height);
            v_src_row_base = u_src_row_base + (src_stride * height);

            y_dst_row_base = dst;
            uv_dst_row_base = y_dst_row_base + (y_dst_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv444p_to_yuv420_line_stripe(y_src_row_base, u_src_row_base, v_src_row_base,
                                                            y_dst_row_base, uv_dst_row_base, &dst_order,
                                                            width, row);

                y_src_row_base += src_stride;
                u_src_row_base += src_stride;
                v_src_row_base += src_stride;
                
                y_dst_row_base += y_dst_stride;
                if ((row % 2) != 0)
                {
                    uv_dst_row_base += uv_dst_stride;
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

static inline pixctrl_result_t pixctrl_generic_core_yuv422p_to_yuv444(const pixctrl_yuv_order_t dst_order,
                                                                      uint8_t *src, uint8_t *dst, 
                                                                      int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = NULL;
    uint8_t *u_src_row_base = NULL;
    uint8_t *v_src_row_base = NULL;
    uint8_t *dst_row_base = dst;
    register int32_t y_src_stride = width;
    register int32_t uv_src_stride = width / 2;
    register int32_t yuv_dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if ((width % 2) == 0)
        {
            y_src_row_base = src;
            u_src_row_base = y_src_row_base + (y_src_stride * height);
            v_src_row_base = u_src_row_base + (uv_src_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv422p_to_yuv444_line_stripe(y_src_row_base, u_src_row_base, v_src_row_base,
                                                              dst_row_base, &dst_order,
                                                              width);

                y_src_row_base += y_src_stride;
                u_src_row_base += uv_src_stride;
                v_src_row_base += uv_src_stride;
                
                dst_row_base += yuv_dst_stride;
            }
        }
        else
        {
            result = PIXCTRL_INVALID_RANGE;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_yuv422p_to_yuv422(const pixctrl_yuv_order_t dst_order,
                                                                      uint8_t *src, uint8_t *dst, 
                                                                      int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = NULL;
    uint8_t *u_src_row_base = NULL;
    uint8_t *v_src_row_base = NULL;
    uint8_t *dst_row_base = dst;
    register int32_t y_src_stride = width;
    register int32_t uv_src_stride = width / 2;
    register int32_t yuv_dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if ((width % 2) == 0)
        {
            y_src_row_base = src;
            u_src_row_base = y_src_row_base + (y_src_stride * height);
            v_src_row_base = u_src_row_base + (uv_src_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv422p_to_yuv422_line_stripe(y_src_row_base, u_src_row_base, v_src_row_base,
                                                              dst_row_base, &dst_order,
                                                              width);

                y_src_row_base += y_src_stride;
                u_src_row_base += uv_src_stride;
                v_src_row_base += uv_src_stride;
                
                dst_row_base += yuv_dst_stride;
            }
        }
        else
        {
            result = PIXCTRL_INVALID_RANGE;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_yuv422p_to_yuv420(const pixctrl_yuv_order_t dst_order,
                                                                      uint8_t *src, uint8_t *dst, 
                                                                      int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = NULL;
    uint8_t *u_src_row_base = NULL;
    uint8_t *v_src_row_base = NULL;
    uint8_t *y_dst_row_base = NULL;
    uint8_t *uv_dst_row_base = NULL;
    register int32_t y_src_stride = width;
    register int32_t uv_src_stride = width / 2;
    register int32_t y_dst_stride = width;
    register int32_t uv_dst_stride = width * (dst_order.bpp / 2);
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            y_src_row_base = src;
            u_src_row_base = y_src_row_base + (y_src_stride * height);
            v_src_row_base = u_src_row_base + (uv_src_stride * height);

            y_dst_row_base = dst;
            uv_dst_row_base = y_dst_row_base + (y_dst_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv422p_to_yuv420_line_stripe(y_src_row_base, u_src_row_base, v_src_row_base,
                                                              y_dst_row_base, uv_dst_row_base, &dst_order,
                                                              width, row);

                y_src_row_base += y_src_stride;
                u_src_row_base += uv_src_stride;
                v_src_row_base += uv_src_stride;
                
                y_dst_row_base += y_dst_stride;
                if ((row % 2) != 0)
                {
                    uv_dst_row_base += uv_dst_stride;
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

static inline pixctrl_result_t pixctrl_generic_core_yuv420p_to_yuv444(const pixctrl_yuv_order_t dst_order,
                                                                      uint8_t *src, uint8_t *dst, 
                                                                      int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = NULL;
    uint8_t *u_src_row_base = NULL;
    uint8_t *v_src_row_base = NULL;
    uint8_t *dst_row_base = dst;
    register int32_t y_src_stride = width;
    register int32_t uv_src_stride = width / 2;
    register int32_t yuv_dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            y_src_row_base = src;
            u_src_row_base = y_src_row_base + (y_src_stride * height);
            v_src_row_base = u_src_row_base + (uv_src_stride * (height / 2));

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv420p_to_yuv444_line_stripe(y_src_row_base, u_src_row_base, v_src_row_base,
                                                              dst_row_base, &dst_order,
                                                              width);

                y_src_row_base += y_src_stride;
                dst_row_base += yuv_dst_stride;
                if ((row % 2) != 0)
                {
                    u_src_row_base += uv_src_stride;
                    v_src_row_base += uv_src_stride;
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

static inline pixctrl_result_t pixctrl_generic_core_yuv420p_to_yuv422(const pixctrl_yuv_order_t dst_order,
                                                                      uint8_t *src, uint8_t *dst, 
                                                                      int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = NULL;
    uint8_t *u_src_row_base = NULL;
    uint8_t *v_src_row_base = NULL;
    uint8_t *dst_row_base = dst;
    register int32_t y_src_stride = width;
    register int32_t uv_src_stride = width / 2;
    register int32_t yuv_dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if ((width % 2) == 0)
        {
            y_src_row_base = src;
            u_src_row_base = y_src_row_base + (y_src_stride * height);
            v_src_row_base = u_src_row_base + (uv_src_stride * (height / 2));

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv420p_to_yuv422_line_stripe(y_src_row_base, u_src_row_base, v_src_row_base,
                                                              dst_row_base, &dst_order,
                                                              width);

                y_src_row_base += y_src_stride;
                if ((row % 2) != 0)
                {
                    u_src_row_base += uv_src_stride;
                    v_src_row_base += uv_src_stride;
                }
                
                dst_row_base += yuv_dst_stride;
            }
        }
        else
        {
            result = PIXCTRL_INVALID_RANGE;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_yuv420p_to_yuv420(const pixctrl_yuv_order_t dst_order,
                                                                      uint8_t *src, uint8_t *dst, 
                                                                      int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *y_src_row_base = NULL;
    uint8_t *u_src_row_base = NULL;
    uint8_t *v_src_row_base = NULL;
    uint8_t *y_dst_row_base = NULL;
    uint8_t *uv_dst_row_base = NULL;
    register int32_t y_src_stride = width;
    register int32_t uv_src_stride = width / 2;
    register int32_t y_dst_stride = width;
    register int32_t uv_dst_stride = width * (dst_order.bpp / 2);
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            y_src_row_base = src;
            u_src_row_base = y_src_row_base + (y_src_stride * height);
            v_src_row_base = u_src_row_base + (uv_src_stride * (height / 2));

            y_dst_row_base = dst;
            uv_dst_row_base = y_dst_row_base + (y_dst_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv422p_to_yuv420_line_stripe(y_src_row_base, u_src_row_base, v_src_row_base,
                                                              y_dst_row_base, uv_dst_row_base, &dst_order,
                                                              width, row);

                y_src_row_base += y_src_stride;
                y_dst_row_base += y_dst_stride;
                if ((row % 2) != 0)
                {
                    u_src_row_base += uv_src_stride;
                    v_src_row_base += uv_src_stride;
                    
                    uv_dst_row_base += uv_dst_stride;
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

static inline pixctrl_result_t pixctrl_generic_core_yuv444p_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    register int32_t row;

    uint8_t *y_src, *u_src, *v_src;
    register int32_t yuv_src_stride = width;
    uint8_t *y_dst, *u_dst, *v_dst;
    register int32_t y_dst_stride = width;
    register int32_t uv_dst_stride = width / 2;

    if (result == PIXCTRL_SUCCESS)
    {
        if ((width % 2) == 0)
        {
            y_src = src;
            u_src = y_src + (yuv_src_stride * height);
            v_src = u_src + (yuv_src_stride * height);

            y_dst = dst;
            u_dst = y_dst + (y_dst_stride * height);
            v_dst = u_dst + (uv_dst_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv444p_to_yuv422p_line_stripe(y_src, u_src, v_src,
                                                               y_dst, u_dst, v_dst,
                                                               width);

                y_src += yuv_src_stride;
                u_src += yuv_src_stride;
                v_src += yuv_src_stride;

                y_dst += y_dst_stride;
                u_dst += uv_dst_stride;
                v_dst += uv_dst_stride;
            }
        }
        else
        {
            result = PIXCTRL_INVALID_RANGE;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_yuv444p_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    register int32_t row;

    uint8_t *y_src, *u_src, *v_src;
    register int32_t yuv_src_stride = width;
    uint8_t *y_dst, *u_dst, *v_dst;
    register int32_t y_dst_stride = width;
    register int32_t uv_dst_stride = width / 2;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            y_src = src;
            u_src = y_src + (yuv_src_stride * height);
            v_src = u_src + (yuv_src_stride * height);

            y_dst = dst;
            u_dst = y_dst + (y_dst_stride * height);
            v_dst = u_dst + (uv_dst_stride * (height / 2));

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv444p_to_yuv420p_line_stripe(y_src, u_src, v_src,
                                                               y_dst, u_dst, v_dst,
                                                               width, row);

                y_src += yuv_src_stride;
                u_src += yuv_src_stride;
                v_src += yuv_src_stride;

                y_dst += y_dst_stride;
                if ((row % 2) != 0)
                {
                    u_dst += uv_dst_stride;
                    v_dst += uv_dst_stride;
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

static inline pixctrl_result_t pixctrl_generic_core_yuv422p_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    register int32_t row;

    uint8_t *y_src, *u_src, *v_src;
    register int32_t y_src_stride = width;
    register int32_t uv_src_stride = width / 2;
    uint8_t *y_dst, *u_dst, *v_dst;
    register int32_t yuv_dst_stride = width;

    if (result == PIXCTRL_SUCCESS)
    {
        if ((width % 2) == 0)
        {
            y_src = src;
            u_src = y_src + (y_src_stride * height);
            v_src = u_src + (uv_src_stride * height);

            y_dst = dst;
            u_dst = y_dst + (yuv_dst_stride * height);
            v_dst = u_dst + (yuv_dst_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv422p_to_yuv444p_line_stripe(y_src, u_src, v_src,
                                                               y_dst, u_dst, v_dst,
                                                               width);

                y_src += y_src_stride;
                u_src += uv_src_stride;
                v_src += uv_src_stride;

                y_dst += yuv_dst_stride;
                u_dst += yuv_dst_stride;
                v_dst += yuv_dst_stride;
            }
        }
        else
        {
            result = PIXCTRL_INVALID_RANGE;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_yuv422p_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    register int32_t row;

    uint8_t *y_src, *u_src, *v_src;
    register int32_t y_src_stride = width;
    register int32_t uv_src_stride = width / 2;
    uint8_t *y_dst, *u_dst, *v_dst;
    register int32_t y_dst_stride = width;
    register int32_t uv_dst_stride = width / 2;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            y_src = src;
            u_src = y_src + (y_src_stride * height);
            v_src = u_src + (uv_src_stride * height);

            y_dst = dst;
            u_dst = y_dst + (y_dst_stride * height);
            v_dst = u_dst + (uv_dst_stride * (height / 2));

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv422p_to_yuv420p_line_stripe(y_src, u_src, v_src,
                                                               y_dst, u_dst, v_dst,
                                                               width, row);

                y_src += y_src_stride;
                u_src += uv_src_stride;
                v_src += uv_src_stride;

                y_dst += y_dst_stride;
                if ((row % 2) != 0)
                {
                    u_dst += uv_dst_stride;
                    v_dst += uv_dst_stride;
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

static inline pixctrl_result_t pixctrl_generic_core_yuv420p_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    register int32_t row;

    uint8_t *y_src, *u_src, *v_src;
    register int32_t y_src_stride = width;
    register int32_t uv_src_stride = width / 2;
    uint8_t *y_dst, *u_dst, *v_dst;
    register int32_t yuv_dst_stride = width;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            y_src = src;
            u_src = y_src + (y_src_stride * height);
            v_src = u_src + (uv_src_stride * (height / 2));

            y_dst = dst;
            u_dst = y_dst + (yuv_dst_stride * height);
            v_dst = u_dst + (yuv_dst_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv420p_to_yuv444p_line_stripe(y_src, u_src, v_src,
                                                               y_dst, u_dst, v_dst,
                                                               width);

                y_src += y_src_stride;
                if ((row % 2) != 0)
                {
                    u_src += uv_src_stride;
                    v_src += uv_src_stride;
                }

                y_dst += yuv_dst_stride;
                u_dst += yuv_dst_stride;
                v_dst += yuv_dst_stride;
            }
        }
        else
        {
            result = PIXCTRL_INVALID_RANGE;
        }
    }

    return result;
}

static inline pixctrl_result_t pixctrl_generic_core_yuv420p_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    register int32_t row;

    uint8_t *y_src, *u_src, *v_src;
    register int32_t y_src_stride = width;
    register int32_t uv_src_stride = width / 2;
    uint8_t *y_dst, *u_dst, *v_dst;
    register int32_t y_dst_stride = width;
    register int32_t uv_dst_stride = width / 2;

    if (result == PIXCTRL_SUCCESS)
    {
        if (((width % 2) == 0) && ((height % 2) == 0))
        {
            y_src = src;
            u_src = y_src + (y_src_stride * height);
            v_src = u_src + (uv_src_stride * (height / 2));

            y_dst = dst;
            u_dst = y_dst + (y_dst_stride * height);
            v_dst = u_dst + (uv_dst_stride * height);

            for (row = 0; row < height; ++row)
            {
                pixctrl_generic_yuv420p_to_yuv422p_line_stripe(y_src, u_src, v_src,
                                                               y_dst, u_dst, v_dst,
                                                               width);

                y_src += y_src_stride;
                if ((row % 2) != 0)
                {
                    u_src += uv_src_stride;
                    v_src += uv_src_stride;
                }

                y_dst += y_dst_stride;
                u_dst += uv_dst_stride;
                v_dst += uv_dst_stride;
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
 *  Interleaved yuv444 to Interleaved yuv422
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_yuv444_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv444_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv444_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv444_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                                 src, dst, width, height);
}

/********************************************************************************************
 *  Interleaved yuv444 to Interleaved yuv420
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_yuv444_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv444_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                 src, dst, width, height);
}

/********************************************************************************************
 *  Interleaved yuv422 to Interleaved yuv444
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_yuyv422_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv444((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yvyu422_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv444((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_uyvy422_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv444((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_vyuy422_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv444((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                 src, dst, width, height);
}

/********************************************************************************************
 *  Interleaved yuv422 to Interleaved yuv420
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_yuyv422_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yvyu422_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_uyvy422_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_vyuy422_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuyv422_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yvyu422_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_uyvy422_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_vyuy422_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                 src, dst, width, height);
}

/********************************************************************************************
 *  Interleaved yuv420 to Interleaved yuv444
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_nv12_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv444((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_nv21_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv444((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                 src, dst, width, height);
}

/********************************************************************************************
 *  Interleaved yuv420 to Interleaved yuv422
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_nv12_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_nv12_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_nv12_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_nv12_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_nv21_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_nv21_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_nv21_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                                 src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_nv21_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                 (const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                                 src, dst, width, height);
}

/********************************************************************************************
 *  Interleaved yuv444 to Planar
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_yuv444_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444_to_yuv444p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv444_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444_to_yuv422p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv444_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444_to_yuv420p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                  src, dst, width, height);
}

/********************************************************************************************
 *  Interleaved yuv422 to Planar
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_yuyv422_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv444p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yvyu422_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv444p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_uyvy422_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv444p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_vyuy422_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv444p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuyv422_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv422p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yvyu422_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv422p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_uyvy422_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv422p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_vyuy422_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv422p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuyv422_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv420p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yvyu422_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv420p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_uyvy422_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv420p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_vyuy422_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422_to_yuv420p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                                  src, dst, width, height);
}

/********************************************************************************************
 *  Interleaved yuv420 to Planar
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_nv12_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv444p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_nv21_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv444p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_nv12_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv422p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_nv21_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv422p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_nv12_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv420p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_nv21_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420_to_yuv420p((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                  src, dst, width, height);
}

/********************************************************************************************
 *  Planar yuv444 to Interleaved
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_yuv444p_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444p_to_yuv444((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv444p_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444p_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv444p_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444p_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv444p_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444p_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv444p_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444p_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv444p_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444p_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv444p_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444p_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                  src, dst, width, height);
}

/********************************************************************************************
 *  Planar yuv422 to Interleaved
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_yuv422p_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422p_to_yuv444((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv422p_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422p_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv422p_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422p_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv422p_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422p_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv422p_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422p_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv422p_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422p_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv422p_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422p_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                  src, dst, width, height);
}

/********************************************************************************************
 *  Planar yuv420 to Interleaved
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_yuv420p_to_yuv444(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420p_to_yuv444((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUV444,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv420p_to_yuyv422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420p_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YUYV422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv420p_to_yvyu422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420p_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_YVYU422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv420p_to_uyvy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420p_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_UYVY422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv420p_to_vyuy422(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420p_to_yuv422((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_VYUY422,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv420p_to_nv12(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420p_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV12,
                                                  src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv420p_to_nv21(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420p_to_yuv420((const pixctrl_yuv_order_t)INIT_PIXCTRL_ORDER_NV21,
                                                  src, dst, width, height);
}

/********************************************************************************************
 *  Planar yuv444 to Planar
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_yuv444p_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444p_to_yuv422p(src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv444p_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv444p_to_yuv420p(src, dst, width, height);
}

/********************************************************************************************
 *  Planar yuv422 to Planar
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_yuv422p_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422p_to_yuv444p(src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv422p_to_yuv420p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv422p_to_yuv420p(src, dst, width, height);
}

/********************************************************************************************
 *  Planar yuv420 to Planar
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_yuv420p_to_yuv444p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420p_to_yuv444p(src, dst, width, height);
}

pixctrl_result_t pixctrl_generic_yuv420p_to_yuv422p(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    return pixctrl_generic_core_yuv420p_to_yuv422p(src, dst, width, height);
}
