#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "pixctrl.h"
#include "test_vector.h"

typedef pixctrl_result_t(*rgb2rgb_vector_entry_t)(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

typedef struct {
    const char *test_name;
    size_t bpp;
    rgb2rgb_vector_entry_t entry;
} rgb2rgb_test_vector_t;

static const rgb2rgb_test_vector_t gsc_rgb2rgb_test_vector[] = {
    { "rgba-to-rgb", 24, pixctrl_generic_rgba_to_rgb, },
    { "rgba-to-bgr", 24, pixctrl_generic_rgba_to_bgr, },
    { "bgra-to-rgb", 24, pixctrl_generic_bgra_to_rgb, },
    { "bgra-to-bgr", 24, pixctrl_generic_bgra_to_bgr, },
};

void test_rgb2rgb_convert(test_image_t *src_img)
{
    int32_t i;

    for (i = 0; i < (int32_t)(sizeof(gsc_rgb2rgb_test_vector) / sizeof(rgb2rgb_test_vector_t)); ++i)
    {
        size_t len = (((size_t)src_img->width * gsc_rgb2rgb_test_vector[i].bpp) / 8) * (size_t)src_img->height;
        uint8_t *buf = (uint8_t *)malloc(len);
        assert(buf != NULL);

        gsc_rgb2rgb_test_vector[i].entry(src_img->buf, buf, src_img->width, src_img->height);
        save_test_image_as_rawdata(NULL, gsc_rgb2rgb_test_vector[i].test_name, buf, src_img->width, src_img->height, len);
        free(buf);
        buf = NULL;
    }
}
