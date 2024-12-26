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
