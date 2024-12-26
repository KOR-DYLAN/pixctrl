#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "pixctrl.h"
#include "test_vector.h"

typedef pixctrl_result_t(*rgb2yuv_vector_entry_t)(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

typedef struct {
    const char *test_name;
    size_t bpp;
    rgb2yuv_vector_entry_t entry;
} rgb2yuv_test_vector_t;

static const rgb2yuv_test_vector_t gsc_rgb2yuv_test_vector[] = {
    /* interleaved */
    { "bgra-to-yuv444-interleaved",  24, pixctrl_generic_bgra_to_yuv444,  },
    { "bgra-to-yuyv422-interleaved", 16, pixctrl_generic_bgra_to_yuyv422, },
    { "bgra-to-yvyu422-interleaved", 16, pixctrl_generic_bgra_to_yvyu422, },
    { "bgra-to-uyvy422-interleaved", 16, pixctrl_generic_bgra_to_uyvy422, },
    { "bgra-to-vyuy422-interleaved", 16, pixctrl_generic_bgra_to_vyuy422, },
    { "bgra-to-nv12-interleaved",    12, pixctrl_generic_bgra_to_nv12,    },
    { "bgra-to-nv21-interleaved",    12, pixctrl_generic_bgra_to_nv21,    },
    /* planar */
    { "bgra-to-yuv444-planar",       24, pixctrl_generic_bgra_to_yuv444p,       },
    { "bgra-to-yuv422-planar",       16, pixctrl_generic_bgra_to_yuv422p,       },
    { "bgra-to-yuv420-planar",       12, pixctrl_generic_bgra_to_yuv420p,       },
};

void test_rgb2yuv_convert(test_image_t *src_img)
{
    int32_t i;
    
    for (i = 0; i < (int32_t)(sizeof(gsc_rgb2yuv_test_vector) / sizeof(rgb2yuv_test_vector_t)); ++i)
    {
        size_t len = (((size_t)src_img->width * gsc_rgb2yuv_test_vector[i].bpp) / 8) * (size_t)src_img->height;
        uint8_t *buf = (uint8_t *)malloc(len);
        assert(buf != NULL);

        gsc_rgb2yuv_test_vector[i].entry(src_img->buf, buf, src_img->width, src_img->height);
        save_test_image_as_rawdata(NULL, gsc_rgb2yuv_test_vector[i].test_name, buf, src_img->width, src_img->height, len);
        free(buf);
        buf = NULL;
    }
}
