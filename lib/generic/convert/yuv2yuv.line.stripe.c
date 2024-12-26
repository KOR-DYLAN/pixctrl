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
#include <stdint.h>
#include "pixctrl.h"

/********************************************************************************************
 *  Interleaved to Interleaved Line-Stripe Function
 ********************************************************************************************
 */
void pixctrl_generic_yuv444_to_yuv422_interleaved_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                              uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                              int32_t width)
{
    register const int32_t s_iy = src_order->iy, d_iy = dst_order->iy;
    register const int32_t s_iu = src_order->iu, d_iu = dst_order->iu;
    register const int32_t s_iv = src_order->iv, d_iv = dst_order->iv;
    register const int32_t src_bpp = src_order->bpp, dst_bpp = dst_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = src;
    register uint8_t *dst_pos = dst;
    register uint8_t *prev_dst_pos = NULL;

    register uint32_t u_val = 0U;
    register uint32_t v_val = 0U;

    for(col = 0; col < width; ++col)
    {
        /* Move YUV value */
        dst_pos[d_iy] = src_pos[s_iy];
        u_val += src_pos[s_iu];
        v_val += src_pos[s_iv];

        if ((col % 2) != 0)
        {
            /* Average Each U, V Value */
            u_val = u_val >> 1; /* == (u_val / 2) */
            v_val = v_val >> 1; /* == (v_val / 2) */

            /* Set Each U, V Value */
            prev_dst_pos[d_iu] = (uint8_t)u_val;
            prev_dst_pos[d_iv] = (uint8_t)v_val;

            /* Clear Each Temp U, V Value */
            u_val = 0U;
            v_val = 0U;
        }

        src_pos += src_bpp;
        prev_dst_pos = dst_pos;
        dst_pos += dst_bpp;
    }
}

void pixctrl_generic_yuv444_to_yuv420_interleaved_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                              uint8_t *y_dst, uint8_t *uv_dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                              int32_t width, int32_t row)
{
    register const int32_t s_iy = src_order->iy;
    register const int32_t s_iu = src_order->iu, d_iu = uv_dst_order->iu;
    register const int32_t s_iv = src_order->iv, d_iv = uv_dst_order->iv;
    register const int32_t src_bpp = src_order->bpp, uv_dst_bpp = uv_dst_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = src;
    register uint8_t *uv_dst_pos = uv_dst;

    register uint32_t u_val = 0U;
    register uint32_t v_val = 0U;

    for(col = 0; col < width; ++col)
    {
        /* Move YUV value */
        y_dst[col] = src_pos[s_iy];
        u_val += src_pos[s_iu];
        v_val += src_pos[s_iv];

        if ((col % 2) != 0)
        {
            /* Average Each U, V Value */
            u_val = u_val >> 1; /* == (u_val / 2) */
            v_val = v_val >> 1; /* == (v_val / 2) */

            if ((row % 2) == 0)
            {
                /* Set Each U, V Value */
                uv_dst_pos[d_iu] = (uint8_t)u_val;
                uv_dst_pos[d_iv] = (uint8_t)v_val;
            }
            else
            {
                /* Set Final Each U, V Value */
                u_val = (u_val + (uint32_t)uv_dst_pos[d_iu]) >> 1;
                v_val = (v_val + (uint32_t)uv_dst_pos[d_iv]) >> 1;
                uv_dst_pos[d_iu] = (uint8_t)u_val;
                uv_dst_pos[d_iv] = (uint8_t)v_val;
            }

            /* Clear Each Temp U, V Value */
            u_val = 0U;
            v_val = 0U;

            uv_dst_pos += uv_dst_bpp;
        }

        src_pos += src_bpp;
    }
}

void pixctrl_generic_yuv422_to_yuv444_interleaved_line_stripe(uint8_t *y_src, uint8_t *uv_src, const pixctrl_yuv_order_t *uv_src_order,
                                                              uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                              int32_t width)
{
    register const int32_t s_iy = uv_src_order->iy, d_iy = dst_order->iy;
    register const int32_t s_iu = uv_src_order->iu, d_iu = dst_order->iu;
    register const int32_t s_iv = uv_src_order->iv, d_iv = dst_order->iv;
    register const int32_t src_bpp = uv_src_order->bpp, uv_dst_bpp = dst_order->bpp;

    register int32_t col;
    register uint8_t *uv_src_pos = uv_src;
    register uint8_t *dst_pos = dst;

    register uint32_t u_val = 0U;
    register uint32_t v_val = 0U;

    for(col = 0; col < width; ++col)
    {

    }
}

void pixctrl_generic_yuv422_to_yuv420_interleaved_line_stripe(uint8_t *y_src, uint8_t *uv_src, const pixctrl_yuv_order_t *uv_src_order,
                                                              uint8_t *y_dst, uint8_t *uv_dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                              int32_t width, int32_t row)
{
    register const int32_t s_iy = uv_src_order->iy;
    register const int32_t s_iu = uv_src_order->iu, d_iu = uv_dst_order->iu;
    register const int32_t s_iv = uv_src_order->iv, d_iv = uv_dst_order->iv;
    register const int32_t src_bpp = uv_src_order->bpp, uv_dst_bpp = uv_dst_order->bpp;

    register int32_t col;
    register uint8_t *uv_src_pos = uv_src;
    register uint8_t *uv_dst_pos = uv_dst;

    register uint32_t u_val = 0U;
    register uint32_t v_val = 0U;

    for(col = 0; col < width; ++col)
    {

    }
}

void pixctrl_generic_yuv420_to_yuv444_interleaved_line_stripe(uint8_t *y_src, uint8_t *uv_src, const pixctrl_yuv_order_t *uv_src_order,
                                                              uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                              int32_t width, int32_t row)
{
    register const int32_t s_iy = uv_src_order->iy, d_iy = dst_order->iy;
    register const int32_t s_iu = uv_src_order->iu, d_iu = dst_order->iu;
    register const int32_t s_iv = uv_src_order->iv, d_iv = dst_order->iv;
    register const int32_t src_bpp = uv_src_order->bpp, uv_dst_bpp = dst_order->bpp;

    register int32_t col;
    register uint8_t *uv_src_pos = uv_src;
    register uint8_t *dst_pos = dst;

    register uint32_t u_val = 0U;
    register uint32_t v_val = 0U;

    for(col = 0; col < width; ++col)
    {

    }
}

void pixctrl_generic_yuv420_to_yuv422_interleaved_line_stripe(uint8_t *y_src, uint8_t *uv_src, const pixctrl_yuv_order_t *uv_src_order,
                                                              uint8_t *dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                              int32_t width, int32_t row)
{
    register const int32_t                          d_iy = uv_dst_order->iy;
    register const int32_t s_iu = uv_src_order->iu, d_iu = uv_dst_order->iu;
    register const int32_t s_iv = uv_src_order->iv, d_iv = uv_dst_order->iv;
    register const int32_t src_bpp = uv_src_order->bpp, uv_dst_bpp = uv_dst_order->bpp;

    register int32_t col;
    register uint8_t *uv_src_pos = uv_src;
    register uint8_t *dst_pos = dst;
    register uint8_t *prev_dst_pos = NULL;

    register uint32_t u_val = 0U;
    register uint32_t v_val = 0U;

    for(col = 0; col < width; ++col)
    {

    }
}


/********************************************************************************************
 *  Interleaved to Planar Line-Stripe Function
 ********************************************************************************************
 */
/********************************************************************************************
 *  Planar to Interleaved Line-Stripe Function
 ********************************************************************************************
 */
/********************************************************************************************
 *  Planar to Planar Line-Stripe Function
 ********************************************************************************************
 */
