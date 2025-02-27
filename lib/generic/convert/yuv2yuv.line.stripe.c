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
void pixctrl_generic_yuv444_to_yuv422_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                  uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                  int32_t width)
{
    register const int32_t s_iy = src_order->iy, d_iy = dst_order->iy;
    register const int32_t s_iu = src_order->iu, d_iu = dst_order->iu;
    register const int32_t s_iv = src_order->iv, d_iv = dst_order->iv;
    register const int32_t src_bpp = src_order->bpp, dst_bpp = dst_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = NULL;
    register uint8_t *dst_pos = NULL;

    register uint32_t u_val = 0U;
    register uint32_t v_val = 0U;

    /* convert 'Y' */
    src_pos = src;
    dst_pos = dst;
    for (col = 0; col < width; ++col)
    {
        dst_pos[d_iy] = src_pos[s_iy];
        src_pos += src_bpp;
        dst_pos += dst_bpp;
    }

    /* convert 'CbCr' */
    src_pos = src;
    dst_pos = dst;
    for (col = 0; col < width; col += 2)
    {
        u_val = src_pos[s_iu];
        v_val = src_pos[s_iv];
        src_pos += src_bpp;

        u_val += src_pos[s_iu];
        v_val += src_pos[s_iv];
        src_pos += src_bpp;

        u_val = u_val >> 1; /* == (u_val / 2) */
        v_val = v_val >> 1; /* == (v_val / 2) */

        dst_pos[d_iu] = (uint8_t)u_val;
        dst_pos[d_iv] = (uint8_t)v_val;
        dst_pos += (dst_bpp * 2);
    }
}

void pixctrl_generic_yuv444_to_yuv420_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                  uint8_t *y_dst, uint8_t *uv_dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                  int32_t width, int32_t row)
{
    register const int32_t s_iy = src_order->iy;
    register const int32_t s_iu = src_order->iu, d_iu = uv_dst_order->iu;
    register const int32_t s_iv = src_order->iv, d_iv = uv_dst_order->iv;
    register const int32_t src_bpp = src_order->bpp, uv_dst_bpp = uv_dst_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = NULL;
    register uint8_t *uv_dst_pos = NULL;

    register uint32_t u_val = 0U;
    register uint32_t v_val = 0U;

    /* convert 'Y' */
    src_pos = src;
    for(col = 0; col < width; ++col)
    {
        y_dst[col] = src_pos[s_iy];
        src_pos += src_bpp;
    }

    /* convert 'CbCr' */
    src_pos = src;
    uv_dst_pos = uv_dst;
    for(col = 0; col < width; col += 2)
    {
        u_val = src_pos[s_iu];
        v_val = src_pos[s_iv];
        src_pos += src_bpp;

        u_val += src_pos[s_iu];
        v_val += src_pos[s_iv];
        src_pos += src_bpp;

        u_val = u_val >> 1; /* == (u_val / 2) */
        v_val = v_val >> 1; /* == (v_val / 2) */

        if ((row % 2) != 0)
        {
            u_val += (uint32_t)uv_dst_pos[d_iu];
            v_val += (uint32_t)uv_dst_pos[d_iv];

            u_val = u_val >> 1; /* == (u_val / 2) */
            v_val = v_val >> 1; /* == (v_val / 2) */
        }

        uv_dst_pos[d_iu] = (uint8_t)u_val;
        uv_dst_pos[d_iv] = (uint8_t)v_val;
        uv_dst_pos += uv_dst_bpp;
    }
}

void pixctrl_generic_yuv422_to_yuv444_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *uv_src_order,
                                                  uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                  int32_t width)
{
    register const int32_t s_iy = uv_src_order->iy, d_iy = dst_order->iy;
    register const int32_t s_iu = uv_src_order->iu, d_iu = dst_order->iu;
    register const int32_t s_iv = uv_src_order->iv, d_iv = dst_order->iv;
    register const int32_t src_bpp = uv_src_order->bpp, dst_bpp = dst_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = NULL;
    register uint8_t *dst_pos = NULL;

    /* convert 'Y' */
    src_pos = src;
    dst_pos = dst;
    for(col = 0; col < width; ++col)
    {
        dst_pos[d_iy] = src_pos[s_iy];
        src_pos += src_bpp;
        dst_pos += dst_bpp;
    }

    /* convert 'CbCr' */
    src_pos = src;
    dst_pos = dst;
    for(col = 0; col < width; col += 2)
    {
        dst_pos[d_iu] = src_pos[s_iu];
        dst_pos[d_iv] = src_pos[s_iv];
        dst_pos += dst_bpp;

        dst_pos[d_iu] = src_pos[s_iu];
        dst_pos[d_iv] = src_pos[s_iv];
        dst_pos += dst_bpp;

        src_pos += (src_bpp * 2);
    }
}

void pixctrl_generic_yuv422_to_yuv420_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *uv_src_order,
                                                  uint8_t *y_dst, uint8_t *uv_dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                  int32_t width, int32_t row)
{
    register const int32_t s_iy = uv_src_order->iy;
    register const int32_t s_iu = uv_src_order->iu, d_iu = uv_dst_order->iu;
    register const int32_t s_iv = uv_src_order->iv, d_iv = uv_dst_order->iv;
    register const int32_t src_bpp = uv_src_order->bpp, uv_dst_bpp = uv_dst_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = NULL;
    register uint8_t *uv_dst_pos = NULL;

    register uint32_t u_val = 0U;
    register uint32_t v_val = 0U;

    /* convert 'Y' */
    src_pos = src;
    for(col = 0; col < width; ++col)
    {
        y_dst[col] = src_pos[s_iy];
        src_pos += src_bpp;
    }

    /* convert 'CbCr' */
    src_pos = src;
    uv_dst_pos = uv_dst;
    for(col = 0; col < width; col += 2)
    {
        u_val = src_pos[s_iu];
        v_val = src_pos[s_iv];
        src_pos += (src_bpp * 2);

        if ((row % 2) != 0)
        {
            u_val += (uint32_t)uv_dst_pos[d_iu];
            v_val += (uint32_t)uv_dst_pos[d_iv];

            u_val = u_val >> 1; /* == (u_val / 2) */
            v_val = v_val >> 1; /* == (v_val / 2) */
        }

        uv_dst_pos[d_iu] = (uint8_t)u_val;
        uv_dst_pos[d_iv] = (uint8_t)v_val;

        uv_dst_pos += uv_dst_bpp;
    }
}

void pixctrl_generic_yuv420_to_yuv444_line_stripe(uint8_t *y_src, uint8_t *uv_src, const pixctrl_yuv_order_t *uv_src_order,
                                                  uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                  int32_t width)
{
    register const int32_t                          d_iy = dst_order->iy;
    register const int32_t s_iu = uv_src_order->iu, d_iu = dst_order->iu;
    register const int32_t s_iv = uv_src_order->iv, d_iv = dst_order->iv;
    register const int32_t src_bpp = uv_src_order->bpp, dst_bpp = dst_order->bpp;

    register int32_t col;
    register uint8_t *uv_src_pos = NULL;
    register uint8_t *dst_pos = NULL;

    /* convert 'Y' */
    dst_pos = dst;
    for(col = 0; col < width; ++col)
    {
        dst_pos[d_iy] = y_src[col];
        dst_pos += dst_bpp;
    }

    /* convert 'CbCr' */
    uv_src_pos = uv_src;
    dst_pos = dst;
    for(col = 0; col < width; col += 2)
    {
        dst_pos[d_iu] = uv_src_pos[s_iu];
        dst_pos[d_iv] = uv_src_pos[s_iv];
        dst_pos += dst_bpp;

        dst_pos[d_iu] = uv_src_pos[s_iu];
        dst_pos[d_iv] = uv_src_pos[s_iv];
        dst_pos += dst_bpp;

        uv_src_pos += src_bpp;
    }
}

void pixctrl_generic_yuv420_to_yuv422_line_stripe(uint8_t *y_src, uint8_t *uv_src, const pixctrl_yuv_order_t *uv_src_order,
                                                  uint8_t *dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                  int32_t width)
{
    register const int32_t                          d_iy = uv_dst_order->iy;
    register const int32_t s_iu = uv_src_order->iu, d_iu = uv_dst_order->iu;
    register const int32_t s_iv = uv_src_order->iv, d_iv = uv_dst_order->iv;
    register const int32_t uv_src_bpp = uv_src_order->bpp, dst_bpp = uv_dst_order->bpp;

    register int32_t col;
    register uint8_t *uv_src_pos = NULL;
    register uint8_t *dst_pos = NULL;

    /* convert 'Y' */
    dst_pos = dst;
    for(col = 0; col < width; ++col)
    {
        dst_pos[d_iy] = y_src[col];
        dst_pos += dst_bpp;
    }

    /* convert 'CbCr' */
    uv_src_pos = uv_src;
    dst_pos = dst;
    for(col = 0; col < width; col += 2)
    {
        dst_pos[d_iu] = uv_src_pos[s_iu];
        dst_pos[d_iv] = uv_src_pos[s_iv];
        uv_src_pos += uv_src_bpp;
        dst_pos += (dst_bpp * 2);
    }
}

/********************************************************************************************
 *  Interleaved to Planar Line-Stripe Function
 ********************************************************************************************
 */
/* from yuv444 */
void pixctrl_generic_yuv444_to_yuv444p_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                   uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                   int32_t width)
{
    register const int32_t s_iy = src_order->iy;
    register const int32_t s_iu = src_order->iu;
    register const int32_t s_iv = src_order->iv;
    register const int32_t src_bpp = src_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = src;

    for(col = 0; col < width; ++col)
    {
        y_dst[col] = src_pos[s_iy];
        u_dst[col] = src_pos[s_iu];
        v_dst[col] = src_pos[s_iv];
        src_pos += src_bpp;
    }
}

void pixctrl_generic_yuv444_to_yuv422p_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                   uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                   int32_t width)
{
    register const int32_t s_iy = src_order->iy;
    register const int32_t s_iu = src_order->iu;
    register const int32_t s_iv = src_order->iv;
    register const int32_t src_bpp = src_order->bpp;

    register int32_t col, uv_col;
    register uint8_t *src_pos = NULL;

    register uint32_t u_val = 0;
    register uint32_t v_val = 0;

    /* convert 'Y' */
    src_pos = src;
    for(col = 0; col < width; ++col)
    {
        y_dst[col]  = src_pos[s_iy];
        src_pos += src_bpp;
    }

    /* convert 'CbCr' */
    src_pos = src;
    for(col = 0; col < width; col += 2)
    {
        u_val = src_pos[s_iu];
        v_val = src_pos[s_iv];
        src_pos += src_bpp;

        u_val += src_pos[s_iu];
        v_val += src_pos[s_iv];
        src_pos += src_bpp;

        u_val = u_val >> 1; /* == (u_val / 2) */
        v_val = v_val >> 1; /* == (u_val / 2) */

        uv_col = col / 2;
        u_dst[uv_col] = (uint8_t)u_val;
        v_dst[uv_col] = (uint8_t)v_val;
    }
}

void pixctrl_generic_yuv444_to_yuv420p_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                   uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                   int32_t width, int32_t row)
{
    register const int32_t s_iy = src_order->iy;
    register const int32_t s_iu = src_order->iu;
    register const int32_t s_iv = src_order->iv;
    register const int32_t src_bpp = src_order->bpp;

    register int32_t col, uv_col;
    register uint8_t *src_pos = NULL;

    register uint32_t u_val = 0;
    register uint32_t v_val = 0;

    /* convert 'Y' */
    src_pos = src;
    for(col = 0; col < width; ++col)
    {
        y_dst[col]  = src_pos[s_iy];
        src_pos += src_bpp;
    }

    /* convert 'CbCr' */
    src_pos = src;
    for(col = 0; col < width; col += 2)
    {
        u_val = src_pos[s_iu];
        v_val = src_pos[s_iv];
        src_pos += src_bpp;

        u_val += src_pos[s_iu];
        v_val += src_pos[s_iv];
        src_pos += src_bpp;

        u_val = u_val >> 1; /* == (u_val / 2) */
        v_val = v_val >> 1; /* == (u_val / 2) */

        uv_col = col / 2;
        if ((row % 2) != 0)
        {
            u_val += (uint32_t)u_dst[uv_col];
            v_val += (uint32_t)v_dst[uv_col];

            u_val = u_val >> 1; /* == (u_val / 2) */
            v_val = v_val >> 1; /* == (v_val / 2) */
        }
        u_dst[uv_col] = (uint8_t)u_val;
        v_dst[uv_col] = (uint8_t)v_val;
    }
}

/* from yuv422 */
void pixctrl_generic_yuv422_to_yuv444p_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                   uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                   int32_t width)
{
    register const int32_t s_iy = src_order->iy;
    register const int32_t s_iu = src_order->iu;
    register const int32_t s_iv = src_order->iv;
    register const int32_t src_bpp = src_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = src;

    /* convert 'Y' */
    src_pos = src;
    for(col = 0; col < width; ++col)
    {
        y_dst[col]  = src_pos[s_iy];
        src_pos += src_bpp;
    }

    /* convert 'CbCr' */
    src_pos = src;
    for(col = 0; col < width; col += 2)
    {
        u_dst[col] = src_pos[s_iu];
        v_dst[col] = src_pos[s_iv];

        u_dst[col + 1] = src_pos[s_iu];
        v_dst[col + 1] = src_pos[s_iv];

        src_pos += (src_bpp * 2);
    }
}

void pixctrl_generic_yuv422_to_yuv422p_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                   uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                   int32_t width)
{
    register const int32_t s_iy = src_order->iy;
    register const int32_t s_iu = src_order->iu;
    register const int32_t s_iv = src_order->iv;
    register const int32_t src_bpp = src_order->bpp;

    register int32_t col, uv_col = 0;
    register uint8_t *src_pos = NULL;

    /* convert 'Y' */
    src_pos = src;
    for(col = 0; col < width; ++col)
    {
        y_dst[col]  = src_pos[s_iy];
        src_pos += src_bpp;
    }

    /* convert 'CbCr' */
    src_pos = src;
    for(col = 0; col < width; col += 2)
    {
        uv_col = col / 2;
        u_dst[uv_col] = src_pos[s_iu];
        v_dst[uv_col] = src_pos[s_iv];
        src_pos += (src_bpp * 2);
    }
}

void pixctrl_generic_yuv422_to_yuv420p_line_stripe(uint8_t *src, const pixctrl_yuv_order_t *src_order,
                                                   uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                   int32_t width, int32_t row)
{
    register const int32_t s_iy = src_order->iy;
    register const int32_t s_iu = src_order->iu;
    register const int32_t s_iv = src_order->iv;
    register const int32_t src_bpp = src_order->bpp;

    register int32_t col, uv_col = 0;
    register uint8_t *src_pos = NULL;

    register uint32_t u_val = 0;
    register uint32_t v_val = 0;

    /* convert 'Y' */
    src_pos = src;
    for(col = 0; col < width; ++col)
    {
        y_dst[col]  = src_pos[s_iy];
        src_pos += src_bpp;
    }

    /* convert 'CbCr' */
    src_pos = src;
    for(col = 0; col < width; col += 2)
    {
        uv_col = col / 2;

        u_val = src_pos[s_iu];
        v_val = src_pos[s_iv];

        if ((row % 2) != 0)
        {
            u_val += (uint32_t)u_dst[uv_col];
            v_val += (uint32_t)v_dst[uv_col];

            u_val = u_val >> 1; /* == (u_val / 2) */
            v_val = v_val >> 1; /* == (v_val / 2) */
        }

        u_dst[uv_col] = (uint8_t)u_val;
        v_dst[uv_col] = (uint8_t)v_val;
        src_pos += (src_bpp * 2);
    }
}

/* from yuv420 */
void pixctrl_generic_yuv420_to_yuv444p_line_stripe(uint8_t *y_src, uint8_t *uv_src, const pixctrl_yuv_order_t *uv_src_order,
                                                   uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                   int32_t width)
{
    register const int32_t s_iu = uv_src_order->iu;
    register const int32_t s_iv = uv_src_order->iv;
    register const int32_t src_bpp = uv_src_order->bpp;

    register int32_t col;
    register uint8_t *uv_src_pos = NULL;

    /* convert 'Y' */
    for(col = 0; col < width; ++col)
    {
        y_dst[col] = y_src[col];
    }

    /* convert 'CbCr' */
    uv_src_pos = uv_src;
    for(col = 0; col < width; col += 2)
    {
        u_dst[col] = uv_src_pos[s_iu];
        v_dst[col] = uv_src_pos[s_iv];

        u_dst[col + 1] = uv_src_pos[s_iu];
        v_dst[col + 1] = uv_src_pos[s_iv];

        uv_src_pos += src_bpp;
    }
}

void pixctrl_generic_yuv420_to_yuv422p_line_stripe(uint8_t *y_src, uint8_t *uv_src, const pixctrl_yuv_order_t *uv_src_order,
                                                   uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                   int32_t width)
{
    register const int32_t s_iu = uv_src_order->iu;
    register const int32_t s_iv = uv_src_order->iv;
    register const int32_t src_bpp = uv_src_order->bpp;

    register int32_t col, uv_col;
    register uint8_t *uv_src_pos = NULL;

    /* convert 'Y' */
    for(col = 0; col < width; ++col)
    {
        y_dst[col] = y_src[col];
    }

    /* convert 'CbCr' */
    uv_src_pos = uv_src;
    for(col = 0; col < width; col += 2)
    {
        uv_col = col / 2;
        u_dst[uv_col] = uv_src_pos[s_iu];
        v_dst[uv_col] = uv_src_pos[s_iv];
        uv_src_pos += src_bpp;
    }
}

void pixctrl_generic_yuv420_to_yuv420p_line_stripe(uint8_t *y_src, uint8_t *uv_src, const pixctrl_yuv_order_t *uv_src_order,
                                                   uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                   int32_t width, int32_t row)
{
    register const int32_t s_iu = uv_src_order->iu;
    register const int32_t s_iv = uv_src_order->iv;
    register const int32_t src_bpp = uv_src_order->bpp;

    register int32_t col, uv_col;
    register uint8_t *uv_src_pos = NULL;

    /* convert 'Y' */
    for(col = 0; col < width; ++col)
    {
        y_dst[col] = y_src[col];
    }

    /* convert 'CbCr' */
    uv_src_pos = uv_src;
    for(col = 0; col < width; col += 2)
    {
        uv_col = col / 2;
        u_dst[uv_col] = uv_src_pos[s_iu];
        v_dst[uv_col] = uv_src_pos[s_iv];
        uv_src_pos += src_bpp;
    }
}

/********************************************************************************************
 *  Planar to Interleaved Line-Stripe Function
 ********************************************************************************************
 */
/* from yuv444p */
void pixctrl_generic_yuv444p_to_yuv444_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                   uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                   int32_t width)
{
    register const int32_t d_iy = dst_order->iy;
    register const int32_t d_iu = dst_order->iu;
    register const int32_t d_iv = dst_order->iv;
    register const int32_t dst_bpp = dst_order->bpp;

    register int32_t col;
    register uint8_t *dst_pos = dst;

    for(col = 0; col < width; ++col)
    {
        dst_pos[d_iy] = y_src[col];
        dst_pos[d_iu] = u_src[col];
        dst_pos[d_iv] = v_src[col];
        dst_pos += dst_bpp;
    }
}

void pixctrl_generic_yuv444p_to_yuv422_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                   uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                   int32_t width)
{
    register const int32_t d_iy = dst_order->iy;
    register const int32_t d_iu = dst_order->iu;
    register const int32_t d_iv = dst_order->iv;
    register const int32_t dst_bpp = dst_order->bpp;

    register int32_t col;
    register uint8_t *dst_pos = dst;

    register uint32_t u_val = 0;
    register uint32_t v_val = 0;

    /* convert 'Y' */
    dst_pos = dst;
    for(col = 0; col < width; ++col)
    {
        dst_pos[d_iy] = y_src[col];
        dst_pos += dst_bpp;
    }

    /* convert 'CbCr' */
    dst_pos = dst;
    for(col = 0; col < width; col += 2)
    {
        u_val = (uint32_t)u_src[col];
        v_val = (uint32_t)v_src[col];

        u_val += (uint32_t)u_src[col + 1];
        v_val += (uint32_t)v_src[col + 1];

        u_val = u_val >> 1;
        v_val = v_val >> 1;

        dst_pos[d_iu] = (uint8_t)u_val;
        dst_pos[d_iv] = (uint8_t)v_val;
        dst_pos += (dst_bpp * 2);
    }
}

void pixctrl_generic_yuv444p_to_yuv420_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                   uint8_t *y_dst, uint8_t *uv_dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                   int32_t width, int32_t row)
{
    register const int32_t d_iu = uv_dst_order->iu;
    register const int32_t d_iv = uv_dst_order->iv;
    register const int32_t dst_bpp = uv_dst_order->bpp;

    register int32_t col;
    register uint8_t *uv_dst_pos = uv_dst;

    register uint32_t u_val = 0;
    register uint32_t v_val = 0;

    /* convert 'Y' */
    for(col = 0; col < width; ++col)
    {
        y_dst[col] = y_src[col];
    }

    /* convert 'CbCr' */
    uv_dst_pos = uv_dst;
    for(col = 0; col < width; col += 2)
    {
        u_val = (uint32_t)u_src[col];
        v_val = (uint32_t)v_src[col];

        u_val += (uint32_t)u_src[col + 1];
        v_val += (uint32_t)v_src[col + 1];

        u_val = u_val >> 1; /* == (u_val / 2) */
        v_val = v_val >> 1; /* == (v_val / 2) */

        u_val = (uint32_t)u_src[col];
        v_val = (uint32_t)v_src[col];

        u_val += (uint32_t)u_src[col + 1];
        v_val += (uint32_t)v_src[col + 1];

        u_val = u_val >> 1;
        v_val = v_val >> 1;

        if ((row % 2) != 0)
        {
            u_val += (uint32_t)uv_dst_pos[d_iu];
            v_val += (uint32_t)uv_dst_pos[d_iv];

            u_val = u_val >> 1;
            v_val = v_val >> 1;
        }

        uv_dst_pos[d_iu] = (uint8_t)u_val;
        uv_dst_pos[d_iv] = (uint8_t)v_val;
        uv_dst_pos += dst_bpp;
    }
}

/* from yuv422p */
void pixctrl_generic_yuv422p_to_yuv444_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                   uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                   int32_t width)
{
    register const int32_t d_iy = dst_order->iy;
    register const int32_t d_iu = dst_order->iu;
    register const int32_t d_iv = dst_order->iv;
    register const int32_t dst_bpp = dst_order->bpp;

    register uint8_t *dst_pos = dst;
    register int32_t col, uv_col;

    for(col = 0; col < width; ++col)
    {
        uv_col = col / 2;
        dst_pos[d_iy] = y_src[col];
        dst_pos[d_iu] = u_src[uv_col];
        dst_pos[d_iv] = v_src[uv_col];
        dst_pos += dst_bpp;
    }
}

void pixctrl_generic_yuv422p_to_yuv422_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                   uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                   int32_t width)
{
    register const int32_t d_iy = dst_order->iy;
    register const int32_t d_iu = dst_order->iu;
    register const int32_t d_iv = dst_order->iv;
    register const int32_t dst_bpp = dst_order->bpp;

    register int32_t col, uv_col;
    register uint8_t *dst_pos = dst;

    /* convert 'Y' */
    dst_pos = dst;
    for(col = 0; col < width; ++col)
    {
        dst_pos[d_iy] = y_src[col];
        dst_pos += dst_bpp;
    }

    /* convert 'CbCr' */
    dst_pos = dst;
    for(col = 0; col < width; col += 2)
    {
        uv_col = col / 2;
        dst_pos[d_iu] = u_src[uv_col];
        dst_pos[d_iv] = v_src[uv_col];
        dst_pos += (dst_bpp * 2);
    }
}

void pixctrl_generic_yuv422p_to_yuv420_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                   uint8_t *y_dst, uint8_t *uv_dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                   int32_t width, int32_t row)
{
    register const int32_t d_iu = uv_dst_order->iu;
    register const int32_t d_iv = uv_dst_order->iv;
    register const int32_t dst_bpp = uv_dst_order->bpp;

    register int32_t col, uv_col;
    register uint8_t *uv_dst_pos = uv_dst;

    register uint32_t u_val;
    register uint32_t v_val;

    /* convert 'Y' */
    for(col = 0; col < width; ++col)
    {
        y_dst[col] = y_src[col];
    }

    /* convert 'CbCr' */
    uv_dst_pos = uv_dst;
    for(col = 0; col < width; col += 2)
    {
        uv_col = col / 2;
        u_val = (uint32_t)u_src[uv_col];
        v_val = (uint32_t)v_src[uv_col];

        if ((row % 2) != 0)
        {
            u_val += (uint32_t)uv_dst_pos[d_iu];
            v_val += (uint32_t)uv_dst_pos[d_iv];

            u_val = u_val >> 1; /* == (u_val / 2) */
            v_val = v_val >> 1; /* == (v_val / 2) */
        }

        uv_dst_pos[d_iu] = (uint8_t)u_val;
        uv_dst_pos[d_iv] = (uint8_t)v_val;
        uv_dst_pos += dst_bpp;
    }
}

/* from yuv420p */
void pixctrl_generic_yuv420p_to_yuv444_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                   uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                   int32_t width)
{
    register const int32_t d_iy = dst_order->iy;
    register const int32_t d_iu = dst_order->iu;
    register const int32_t d_iv = dst_order->iv;
    register const int32_t dst_bpp = dst_order->bpp;

    register uint8_t *dst_pos = dst;
    register int32_t col, uv_col;

    for(col = 0; col < width; ++col)
    {
        uv_col = col / 2;
        dst_pos[d_iy] = y_src[col];
        dst_pos[d_iu] = u_src[uv_col];
        dst_pos[d_iv] = v_src[uv_col];
        dst_pos += dst_bpp;
    }
}

void pixctrl_generic_yuv420p_to_yuv422_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                   uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                   int32_t width)
{
    register const int32_t d_iy = dst_order->iy;
    register const int32_t d_iu = dst_order->iu;
    register const int32_t d_iv = dst_order->iv;
    register const int32_t dst_bpp = dst_order->bpp;

    register int32_t col, uv_col;
    register uint8_t *dst_pos = dst;

    /* convert 'Y' */
    dst_pos = dst;
    for(col = 0; col < width; ++col)
    {
        dst_pos[d_iy] = y_src[col];
        dst_pos += dst_bpp;
    }

    /* convert 'CbCr' */
    dst_pos = dst;
    for(col = 0; col < width; col += 2)
    {
        uv_col = col / 2;
        dst_pos[d_iu] = u_src[uv_col];
        dst_pos[d_iv] = v_src[uv_col];
        dst_pos += (dst_bpp * 2);
    }
}

void pixctrl_generic_yuv420p_to_yuv420_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                   uint8_t *y_dst, uint8_t *uv_dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                   int32_t width, int32_t row)
{
    register const int32_t d_iu = uv_dst_order->iu;
    register const int32_t d_iv = uv_dst_order->iv;
    register const int32_t dst_bpp = uv_dst_order->bpp;

    register int32_t col, uv_col;
    register uint8_t *uv_dst_pos = uv_dst;

    /* convert 'Y' */
    for(col = 0; col < width; ++col)
    {
        y_dst[col] = y_src[col];
    }

    /* convert 'CbCr' */
    if ((row % 2) == 0)
    {
        uv_dst_pos = uv_dst;
        for(col = 0; col < width; col += 2)
        {
            uv_col = col / 2;
            uv_dst_pos[d_iu] = u_src[uv_col];
            uv_dst_pos[d_iv] = v_src[uv_col];
            uv_dst_pos += dst_bpp;
        }
    }
}

/********************************************************************************************
 *  Planar to Planar Line-Stripe Function
 ********************************************************************************************
 */
/* from yuv444p */
void pixctrl_generic_yuv444p_to_yuv422p_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                    uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                    int32_t width)
{
    register int32_t col, uv_col;
    register uint32_t u_val;
    register uint32_t v_val;

    /* convert 'Y' */
    for (col = 0; col < width; ++col)
    {
        y_dst[col] = y_src[col];
    }

    /* convert 'UV' */
    for (col = 0; col < width; col += 2)
    {
        u_val = ((uint32_t)u_src[col] + (uint32_t)u_src[col + 1]) >> 1;
        v_val = ((uint32_t)v_src[col] + (uint32_t)v_src[col + 1]) >> 1;

        uv_col = col / 2;
        u_dst[uv_col] = (uint8_t)u_val;
        v_dst[uv_col] = (uint8_t)v_val;
    }
}

void pixctrl_generic_yuv444p_to_yuv420p_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                    uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                    int32_t width, int32_t row)
{
    register int32_t col, uv_col;
    register uint32_t u_val;
    register uint32_t v_val;

    /* convert 'Y' */
    for (col = 0; col < width; ++col)
    {
        y_dst[col] = y_src[col];
    }

    /* convert 'UV' */
    for (col = 0; col < width; col += 2)
    {
        u_val = ((uint32_t)u_src[col] + (uint32_t)u_src[col + 1]) >> 1;
        v_val = ((uint32_t)v_src[col] + (uint32_t)v_src[col + 1]) >> 1;

        uv_col = col / 2;

        if ((row % 2) != 0)
        {
            u_val += (uint32_t)u_dst[uv_col];
            v_val += (uint32_t)v_dst[uv_col];

            u_val = u_val >> 1; /* == (u_val / 2) */
            v_val = v_val >> 1; /* == (v_val / 2) */
        }

        u_dst[uv_col] = (uint8_t)u_val;
        v_dst[uv_col] = (uint8_t)v_val;
    }
}

/* from yuv422p */
void pixctrl_generic_yuv422p_to_yuv444p_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                    uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                    int32_t width)
{
    register int32_t col, uv_col;

    for (col = 0; col < width; ++col)
    {
        uv_col = col / 2;
        y_dst[col] = y_src[col];
        u_dst[col] = u_src[uv_col];
        v_dst[col] = v_src[uv_col];
    }
}

void pixctrl_generic_yuv422p_to_yuv420p_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                    uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                    int32_t width, int32_t row)
{
    register int32_t col, uv_col;
    register int32_t uv_width = width / 2;
    register uint32_t u_val;
    register uint32_t v_val;

    /* convert 'Y' */
    for (col = 0; col < width; ++col)
    {
        y_dst[col] = y_src[col];
    }

    /* convert 'UV' */
    for (uv_col = 0; uv_col < uv_width; ++uv_col)
    {
        u_val = (uint32_t)u_src[uv_col];
        v_val = (uint32_t)v_src[uv_col];

        if ((row % 2) != 0)
        {
            u_val += (uint32_t)u_dst[uv_col];
            v_val += (uint32_t)v_dst[uv_col];

            u_val = u_val >> 1; /* == (u_val / 2) */
            v_val = v_val >> 1; /* == (v_val / 2) */
        }

        u_dst[uv_col] = (uint8_t)u_val;
        v_dst[uv_col] = (uint8_t)v_val;
    }
}

/* from yuv420p */
void pixctrl_generic_yuv420p_to_yuv444p_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                    uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                    int32_t width)
{
    register int32_t col, uv_col;

    for (col = 0; col < width; ++col)
    {
        uv_col = col / 2;
        y_dst[col] = y_src[col];
        u_dst[col] = u_src[uv_col];
        v_dst[col] = v_src[uv_col];
    }
}

void pixctrl_generic_yuv420p_to_yuv422p_line_stripe(uint8_t *y_src, uint8_t *u_src, uint8_t *v_src,
                                                    uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                    int32_t width)
{
    register int32_t col, uv_col;

    for (col = 0; col < width; ++col)
    {
        uv_col = col / 2;
        y_dst[col] = y_src[col];
        u_dst[uv_col] = u_src[uv_col];
        v_dst[uv_col] = v_src[uv_col];
    }
}
