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

void pixctrl_generic_xrgb_to_rgb24_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                               uint8_t *dst, const pixctrl_rgb_order_t *dst_order,
                                               int32_t width)
{
    register const int32_t src_ir  = src_order->ir,  dst_ir  = dst_order->ir;
    register const int32_t src_ig  = src_order->ig,  dst_ig  = dst_order->ig;
    register const int32_t src_ib  = src_order->ib,  dst_ib  = dst_order->ib;
    register const int32_t src_bpp = src_order->bpp, dst_bpp = dst_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = src;
    register uint8_t *dst_pos = dst;

    for(col = 0; col < width; ++col)
    {
        dst_pos[dst_ir] = src_pos[src_ir];
        dst_pos[dst_ig] = src_pos[src_ig];
        dst_pos[dst_ib] = src_pos[src_ib];
        src_pos += src_bpp;
        dst_pos += dst_bpp;
    }
}

void pixctrl_generic_xrgb32_to_argb32_line_stripe(uint8_t *src, const pixctrl_rgb_order_t *src_order,
                                                  uint8_t *dst, const pixctrl_rgb_order_t *dst_order,
                                                  int32_t width)
{
    register const int32_t src_ia  = src_order->ia,  dst_ia  = dst_order->ia;
    register const int32_t src_ir  = src_order->ir,  dst_ir  = dst_order->ir;
    register const int32_t src_ig  = src_order->ig,  dst_ig  = dst_order->ig;
    register const int32_t src_ib  = src_order->ib,  dst_ib  = dst_order->ib;
    register const int32_t src_bpp = src_order->bpp, dst_bpp = dst_order->bpp;

    register int32_t col;
    register uint8_t *src_pos = src;
    register uint8_t *dst_pos = dst;

    for(col = 0; col < width; ++col)
    {
        dst_pos[dst_ia] = src_pos[src_ia];
        dst_pos[dst_ir] = src_pos[src_ir];
        dst_pos[dst_ig] = src_pos[src_ig];
        dst_pos[dst_ib] = src_pos[src_ib];
        src_pos += src_bpp;
        dst_pos += dst_bpp;
    }
}
