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
 *  Interleaved Line-Stripe Function
 ********************************************************************************************
 */
void pixctrl_generic_rgb_to_yuv444_interleaved_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                           uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                           int32_t width)
{
    register const int32_t ir = src_order->ir, iy = dst_order->iy;
    register const int32_t ig = src_order->ig, iu = dst_order->iu;
    register const int32_t ib = src_order->ib, iv = dst_order->iv;
    register const int32_t src_bpp = src_order->bpp, dst_bpp = dst_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = src;
    register uint8_t *dst_pos = dst;

    for(col = 0; col < width; ++col)
    {
        /* Ref) learn.microsoft.com/en-us/windows/win32/medfound/recommended-8-bit-yuv-formats-for-video-rendering
         *  Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16
         *  U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128
         *  V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128
         */
        register int32_t s32_tmp;
        register uint32_t u32_tmp;
        register int32_t r = (int32_t)src_pos[ir];
        register int32_t g = (int32_t)src_pos[ig];
        register int32_t b = (int32_t)src_pos[ib];

        /* Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16 */
        s32_tmp = (66 * r) + (129 * g) + (25 * b) + 128;
        u32_tmp = (uint32_t)s32_tmp;
        u32_tmp = (u32_tmp >> 8) + 16U;
        dst_pos[iy] = (uint8_t)u32_tmp;

        /* U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128 */
        s32_tmp = (-38 * r) + (-74 * g) + (112 * b) + 128;
        u32_tmp = (uint32_t)s32_tmp;
        u32_tmp = (u32_tmp >> 8) + 128U;
        dst_pos[iu] = (uint8_t)u32_tmp;

        /* V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128 */
        s32_tmp = (112 * r) + (-94 * g) + (-18 * b) + 128;
        u32_tmp = (uint32_t)s32_tmp;
        u32_tmp = (u32_tmp >> 8) + 128U;
        dst_pos[iv] = (uint8_t)u32_tmp;

        src_pos += src_bpp;
        dst_pos += dst_bpp;
    }
}

void pixctrl_generic_rgb_to_yuv422_interleaved_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                           uint8_t *dst, const pixctrl_yuv_order_t *dst_order,
                                                           int32_t width)
{
    register const int32_t ir = src_order->ir, iy = dst_order->iy;
    register const int32_t ig = src_order->ig, iu = dst_order->iu;
    register const int32_t ib = src_order->ib, iv = dst_order->iv;
    register const int32_t src_bpp = src_order->bpp, dst_bpp = dst_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = src;
    register uint8_t *dst_pos = dst;
    register uint8_t *prev_dst_pos;

    register uint32_t u_val = 0U;
    register uint32_t v_val = 0U;

    for(col = 0; col < width; ++col)
    {
        /* Ref) learn.microsoft.com/en-us/windows/win32/medfound/recommended-8-bit-yuv-formats-for-video-rendering
         *  Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16
         *  U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128
         *  V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128
         */
        register int32_t s32_tmp;
        register uint32_t u32_tmp;
        register int32_t r = (int32_t)src_pos[ir];
        register int32_t g = (int32_t)src_pos[ig];
        register int32_t b = (int32_t)src_pos[ib];

        /* Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16 */
        s32_tmp = (66 * r) + (129 * g) + (25 * b) + 128;
        u32_tmp = (uint32_t)s32_tmp;
        u32_tmp = (u32_tmp >> 8) + 16U;
        dst_pos[iy] = (uint8_t)u32_tmp;

        /* U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128 */
        s32_tmp = (-38 * r) + (-74 * g) + (112 * b) + 128;
        u32_tmp = (uint32_t)s32_tmp;
        u32_tmp = (u32_tmp >> 8) + 128U;
        u_val += (uint8_t)u32_tmp;

        /* V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128 */
        s32_tmp = (112 * r) + (-94 * g) + (-18 * b) + 128;
        u32_tmp = (uint32_t)s32_tmp;
        u32_tmp = (u32_tmp >> 8) + 128U;
        v_val += (uint8_t)u32_tmp;

        if ((col % 2) != 0)
        {
            /* Average Each U, V Value */
            u_val = u_val >> 1; /* == (u_val / 2) */
            v_val = v_val >> 1; /* == (v_val / 2) */

            /* Set Each U, V Value */
            prev_dst_pos[iu] = (uint8_t)u_val;
            prev_dst_pos[iv] = (uint8_t)v_val;

            /* Clear Each Temp U, V Value */
            u_val = 0U;
            v_val = 0U;
        }

        src_pos += src_bpp;
        prev_dst_pos = dst_pos;
        dst_pos += dst_bpp;
    }
}

void pixctrl_generic_rgb_to_yuv420_interleaved_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                           uint8_t *y_dst, uint8_t *uv_dst, const pixctrl_yuv_order_t *uv_dst_order,
                                                           int32_t width, int32_t row)
{
    register const int32_t ir = src_order->ir;
    register const int32_t ig = src_order->ig, iu = uv_dst_order->iu;
    register const int32_t ib = src_order->ib, iv = uv_dst_order->iv;
    register const int32_t src_bpp = src_order->bpp, uv_dst_bpp = uv_dst_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = src;
    register uint8_t *uv_dst_pos = uv_dst;

    register uint32_t u_val = 0U;
    register uint32_t v_val = 0U;

    for(col = 0; col < width; ++col)
    {
        /* Ref) learn.microsoft.com/en-us/windows/win32/medfound/recommended-8-bit-yuv-formats-for-video-rendering
         *  Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16
         *  U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128
         *  V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128
         */
        register int32_t s32_tmp;
        register uint32_t u32_tmp;
        register int32_t r = (int32_t)src_pos[ir];
        register int32_t g = (int32_t)src_pos[ig];
        register int32_t b = (int32_t)src_pos[ib];

        /* Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16 */
        s32_tmp = (66 * r) + (129 * g) + (25 * b) + 128;
        u32_tmp = (uint32_t)s32_tmp;
        u32_tmp = (u32_tmp >> 8) + 16U;
        y_dst[col] = (uint8_t)u32_tmp;

        /* U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128 */
        s32_tmp = (-38 * r) + (-74 * g) + (112 * b) + 128;
        u32_tmp = (uint32_t)s32_tmp;
        u32_tmp = (u32_tmp >> 8) + 128U;
        u_val += (uint8_t)u32_tmp;

        /* V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128 */
        s32_tmp = (112 * r) + (-94 * g) + (-18 * b) + 128;
        u32_tmp = (uint32_t)s32_tmp;
        u32_tmp = (u32_tmp >> 8) + 128U;
        v_val += (uint8_t)u32_tmp;

        if ((col % 2) != 0)
        {
            /* Average Each U, V Value */
            u_val = u_val >> 1; /* == (u_val / 2) */
            v_val = v_val >> 1; /* == (v_val / 2) */

            if ((row % 2) == 0)
            {
                /* Set Each U, V Value */
                uv_dst_pos[iu] = (uint8_t)u_val;
                uv_dst_pos[iv] = (uint8_t)v_val;
            }
            else
            {
                /* Set Final Each U, V Value */
                u_val = (u_val + (uint32_t)uv_dst_pos[iu]) >> 1;
                v_val = (v_val + (uint32_t)uv_dst_pos[iv]) >> 1;
                uv_dst_pos[iu] = (uint8_t)u_val;
                uv_dst_pos[iv] = (uint8_t)v_val;
            }

            /* Clear Each Temp U, V Value */
            u_val = 0U;
            v_val = 0U;

            uv_dst_pos += uv_dst_bpp;
        }

        src_pos += src_bpp;
    }
}

/********************************************************************************************
 *  Planar Line-Stripe Function
 ********************************************************************************************
 */
void pixctrl_generic_rgb_to_yuv444_planar_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                      uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                      int32_t width)
{
    register const int32_t ir = src_order->ir;
    register const int32_t ig = src_order->ig;
    register const int32_t ib = src_order->ib;
    register const int32_t src_bpp = src_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = src;

    for(col = 0; col < width; ++col)
    {
        /* Ref) learn.microsoft.com/en-us/windows/win32/medfound/recommended-8-bit-yuv-formats-for-video-rendering
         *  Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16
         *  U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128
         *  V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128
         */
        register int32_t s32_tmp;
        register uint32_t u32_tmp;
        register int32_t r = (int32_t)src_pos[ir];
        register int32_t g = (int32_t)src_pos[ig];
        register int32_t b = (int32_t)src_pos[ib];

        /* Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16 */
        s32_tmp = (66 * r) + (129 * g) + (25 * b) + 128;
        u32_tmp = (uint32_t)s32_tmp;
        u32_tmp = (u32_tmp >> 8) + 16U;
        y_dst[col] = (uint8_t)u32_tmp;

        /* U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128 */
        s32_tmp = (-38 * r) + (-74 * g) + (112 * b) + 128;
        u32_tmp = (uint32_t)s32_tmp;
        u32_tmp = (u32_tmp >> 8) + 128U;
        u_dst[col] = (uint8_t)u32_tmp;

        /* V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128 */
        s32_tmp = (112 * r) + (-94 * g) + (-18 * b) + 128;
        u32_tmp = (uint32_t)s32_tmp;
        u32_tmp = (u32_tmp >> 8) + 128U;
        v_dst[col] = (uint8_t)u32_tmp;

        src_pos += src_bpp;
    }
}

void pixctrl_generic_rgb_to_yuv422_planar_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                      uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                      int32_t width)
{

}

void pixctrl_generic_rgb_to_yuv420_planar_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                      uint8_t *y_dst, uint8_t *u_dst, uint8_t *v_dst,
                                                      int32_t width, int32_t heigh)
{

}
