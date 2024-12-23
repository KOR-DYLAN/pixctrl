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
#include "pixctrl.h"

size_t pixctrl_get_image_size(pixctrl_fmt_t fmt, int32_t width, int32_t height)
{
    const size_t bpp32 = 4U;
    const size_t bpp24 = 3U;
    size_t len = 0;

    switch (fmt)
    {
    case PIXCTRL_FMT_RGBA32:
    case PIXCTRL_FMT_BGRA32:
    case PIXCTRL_FMT_ARGB32:
    case PIXCTRL_FMT_ABGR32:
    case PIXCTRL_FMT_RGBX32:
    case PIXCTRL_FMT_BGRX32:
    case PIXCTRL_FMT_XRGB32:
    case PIXCTRL_FMT_XBGR32:
        len = ((size_t)width * bpp32) * (size_t)height; 
        break;
    case PIXCTRL_FMT_BGR24:
    case PIXCTRL_FMT_RGB24:
        len = ((size_t)width * bpp24) * (size_t)height; 
        break;
    default:
        len = 0U;
        break;
    }

    return len;
}

const char *pixctrl_get_format_as_ffmpeg_style_string(pixctrl_fmt_t fmt)
{
    const char *string_as_ffmpeg_style;

    switch (fmt) {
    case PIXCTRL_FMT_RGBA32:
        string_as_ffmpeg_style = "rgba";
        break;
    case PIXCTRL_FMT_BGRA32:
        string_as_ffmpeg_style = "bgra";
        break;
    case PIXCTRL_FMT_ARGB32:
        string_as_ffmpeg_style = "argb";
        break;
    case PIXCTRL_FMT_ABGR32:
        string_as_ffmpeg_style = "abgr";
        break;
    case PIXCTRL_FMT_RGBX32:
        string_as_ffmpeg_style = "rgba";
        break;
    case PIXCTRL_FMT_BGRX32:
        string_as_ffmpeg_style = "bgra";
        break;
    case PIXCTRL_FMT_XRGB32:
        string_as_ffmpeg_style = "argb";
        break;
    case PIXCTRL_FMT_XBGR32:
        string_as_ffmpeg_style = "abgr";
        break;
    case PIXCTRL_FMT_BGR24:
        string_as_ffmpeg_style = "bgr24";
        break;
    case PIXCTRL_FMT_RGB24:
        string_as_ffmpeg_style = "rgb24";
        break;
    default:
        string_as_ffmpeg_style = "unknown";
        break;
    }

    return string_as_ffmpeg_style;
}
