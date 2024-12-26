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
 *  xxxa to xxx Function
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_rgba_to_rgb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_RGBA;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_RGB;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_rgb_to_rgb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

pixctrl_result_t pixctrl_generic_rgba_to_bgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_RGBA;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_BGR;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_rgb_to_rgb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

pixctrl_result_t pixctrl_generic_bgra_to_rgb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_BGRA;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_RGB;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_rgb_to_rgb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

pixctrl_result_t pixctrl_generic_bgra_to_bgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_BGRA;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_BGR;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_rgb_to_rgb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}


/********************************************************************************************
 *  axxx to xxx Function
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_argb_to_rgb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_ARGB;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_RGB;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_rgb_to_rgb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

pixctrl_result_t pixctrl_generic_argb_to_bgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_ARGB;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_BGR;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_rgb_to_rgb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

pixctrl_result_t pixctrl_generic_abgr_to_rgb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_ABGR;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_RGB;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_rgb_to_rgb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

pixctrl_result_t pixctrl_generic_abgr_to_bgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_ABGR;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_BGR;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_rgb_to_rgb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

/********************************************************************************************
 *  xxxa to xxxa Function
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_rgba_to_bgra(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_ABGR;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_BGRA;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_argb_to_argb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

pixctrl_result_t pixctrl_generic_bgra_to_rgba(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_ABGR;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_RGBA;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_argb_to_argb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}


/********************************************************************************************
 *  xxxa to axxx Function
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_rgba_to_abgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_RGBA;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_ABGR;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_argb_to_argb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

pixctrl_result_t pixctrl_generic_bgra_to_argb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_BGRA;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_ARGB;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_argb_to_argb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

/********************************************************************************************
 *  axxx to xxxa Function
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_argb_to_bgra(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_ARGB;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_BGRA;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_argb_to_argb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

pixctrl_result_t pixctrl_generic_abgr_to_rgba(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_ABGR;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_RGBA;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_argb_to_argb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

/********************************************************************************************
 *  axxx to axxx Function
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_argb_to_abgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_ARGB;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_ABGR;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_argb_to_argb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

pixctrl_result_t pixctrl_generic_abgr_to_argb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_ABGR;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_ARGB;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_argb_to_argb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

/********************************************************************************************
 *  xxx to xxx Function
 ********************************************************************************************
 */
pixctrl_result_t pixctrl_generic_rgb_to_bgr(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_RGB;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_BGR;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_rgb_to_rgb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}

pixctrl_result_t pixctrl_generic_bgr_to_rgb(uint8_t *src, uint8_t *dst, int32_t width, int32_t height)
{
    const pixctrl_rgb_order_t src_order = INIT_PIXCTRL_ORDER_BGR;
    const pixctrl_rgb_order_t dst_order = INIT_PIXCTRL_ORDER_RGB;
    pixctrl_result_t result = pixctrl_check_validation_of_parameters(src, dst, width, height);
    uint8_t *src_row_base = src, *dst_row_base = dst;
    register int32_t src_stride = width * src_order.bpp, dst_stride = width * dst_order.bpp;
    register int32_t row;

    if (result == PIXCTRL_SUCCESS)
    {
        for (row = 0; row < height; ++row)
        {
            pixctrl_generic_rgb_to_rgb_line_stripe(src_row_base, &src_order, dst_row_base, &dst_order, width);
            src_row_base += src_stride;
            dst_row_base += dst_stride;
        }
    }

    return result;
}
