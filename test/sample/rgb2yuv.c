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
    const char *src_group;
    const char *src_fmt;
    size_t src_bpp;

    const char *dst_group;
    const char *dst_fmt;
    size_t dst_bpp;

    int32_t width;
    int32_t height;

    rgb2yuv_vector_entry_t entry;
} rgb2yuv_test_vector_t;

static const rgb2yuv_test_vector_t gsc_rgb2yuv_test_vector[] = {
    /* src   src      src  dst    dst         dst
       group fmt      bpp  group  fmt         bpp width height converter */
    { "rgb", "abgr",  32,  "yuv", "yuv444",   24, 1280, 720,   pixctrl_generic_abgr_to_yuv444,   },
    { "rgb", "abgr",  32,  "yuv", "yuyv422",  16, 1280, 720,   pixctrl_generic_abgr_to_yuyv422,  },
    { "rgb", "abgr",  32,  "yuv", "yvyu422",  16, 1280, 720,   pixctrl_generic_abgr_to_yvyu422,  },
    { "rgb", "abgr",  32,  "yuv", "uyvy422",  16, 1280, 720,   pixctrl_generic_abgr_to_uyvy422,  },
    { "rgb", "abgr",  32,  "yuv", "vyuy422",  16, 1280, 720,   pixctrl_generic_abgr_to_vyuy422,  },
    { "rgb", "abgr",  32,  "yuv", "nv12",     12, 1280, 720,   pixctrl_generic_abgr_to_nv12,     },
    { "rgb", "abgr",  32,  "yuv", "nv21",     12, 1280, 720,   pixctrl_generic_abgr_to_nv21,     },
    { "rgb", "abgr",  32,  "yuv", "yuv444p",  24, 1280, 720,   pixctrl_generic_abgr_to_yuv444p,  },
    { "rgb", "abgr",  32,  "yuv", "yuv422p",  16, 1280, 720,   pixctrl_generic_abgr_to_yuv422p,  },
    { "rgb", "abgr",  32,  "yuv", "yuv420p",  12, 1280, 720,   pixctrl_generic_abgr_to_yuv420p,  },

    { "rgb", "argb",  32,  "yuv", "yuv444",   24, 1280, 720,   pixctrl_generic_argb_to_yuv444,   },
    { "rgb", "argb",  32,  "yuv", "yuyv422",  16, 1280, 720,   pixctrl_generic_argb_to_yuyv422,  },
    { "rgb", "argb",  32,  "yuv", "yvyu422",  16, 1280, 720,   pixctrl_generic_argb_to_yvyu422,  },
    { "rgb", "argb",  32,  "yuv", "uyvy422",  16, 1280, 720,   pixctrl_generic_argb_to_uyvy422,  },
    { "rgb", "argb",  32,  "yuv", "vyuy422",  16, 1280, 720,   pixctrl_generic_argb_to_vyuy422,  },
    { "rgb", "argb",  32,  "yuv", "nv12",     12, 1280, 720,   pixctrl_generic_argb_to_nv12,     },
    { "rgb", "argb",  32,  "yuv", "nv21",     12, 1280, 720,   pixctrl_generic_argb_to_nv21,     },
    { "rgb", "argb",  32,  "yuv", "yuv444p",  24, 1280, 720,   pixctrl_generic_argb_to_yuv444p,  },
    { "rgb", "argb",  32,  "yuv", "yuv422p",  16, 1280, 720,   pixctrl_generic_argb_to_yuv422p,  },
    { "rgb", "argb",  32,  "yuv", "yuv420p",  12, 1280, 720,   pixctrl_generic_argb_to_yuv420p,  },

    { "rgb", "bgra",  32,  "yuv", "yuv444",   24, 1280, 720,   pixctrl_generic_bgra_to_yuv444,   },
    { "rgb", "bgra",  32,  "yuv", "yuyv422",  16, 1280, 720,   pixctrl_generic_bgra_to_yuyv422,  },
    { "rgb", "bgra",  32,  "yuv", "yvyu422",  16, 1280, 720,   pixctrl_generic_bgra_to_yvyu422,  },
    { "rgb", "bgra",  32,  "yuv", "uyvy422",  16, 1280, 720,   pixctrl_generic_bgra_to_uyvy422,  },
    { "rgb", "bgra",  32,  "yuv", "vyuy422",  16, 1280, 720,   pixctrl_generic_bgra_to_vyuy422,  },
    { "rgb", "bgra",  32,  "yuv", "nv12",     12, 1280, 720,   pixctrl_generic_bgra_to_nv12,     },
    { "rgb", "bgra",  32,  "yuv", "nv21",     12, 1280, 720,   pixctrl_generic_bgra_to_nv21,     },
    { "rgb", "bgra",  32,  "yuv", "yuv444p",  24, 1280, 720,   pixctrl_generic_bgra_to_yuv444p,  },
    { "rgb", "bgra",  32,  "yuv", "yuv422p",  16, 1280, 720,   pixctrl_generic_bgra_to_yuv422p,  },
    { "rgb", "bgra",  32,  "yuv", "yuv420p",  12, 1280, 720,   pixctrl_generic_bgra_to_yuv420p,  },

    { "rgb", "rgba",  32,  "yuv", "yuv444",   24, 1280, 720,   pixctrl_generic_rgba_to_yuv444,   },
    { "rgb", "rgba",  32,  "yuv", "yuyv422",  16, 1280, 720,   pixctrl_generic_rgba_to_yuyv422,  },
    { "rgb", "rgba",  32,  "yuv", "yvyu422",  16, 1280, 720,   pixctrl_generic_rgba_to_yvyu422,  },
    { "rgb", "rgba",  32,  "yuv", "uyvy422",  16, 1280, 720,   pixctrl_generic_rgba_to_uyvy422,  },
    { "rgb", "rgba",  32,  "yuv", "vyuy422",  16, 1280, 720,   pixctrl_generic_rgba_to_vyuy422,  },
    { "rgb", "rgba",  32,  "yuv", "nv12",     12, 1280, 720,   pixctrl_generic_rgba_to_nv12,     },
    { "rgb", "rgba",  32,  "yuv", "nv21",     12, 1280, 720,   pixctrl_generic_rgba_to_nv21,     },
    { "rgb", "rgba",  32,  "yuv", "yuv444p",  24, 1280, 720,   pixctrl_generic_rgba_to_yuv444p,  },
    { "rgb", "rgba",  32,  "yuv", "yuv422p",  16, 1280, 720,   pixctrl_generic_rgba_to_yuv422p,  },
    { "rgb", "rgba",  32,  "yuv", "yuv420p",  12, 1280, 720,   pixctrl_generic_rgba_to_yuv420p,  },

    { "rgb", "rgb24", 24,  "yuv", "yuv444",   24, 1280, 720,   pixctrl_generic_rgb24_to_yuv444,  },
    { "rgb", "rgb24", 24,  "yuv", "yuyv422",  16, 1280, 720,   pixctrl_generic_rgb24_to_yuyv422, },
    { "rgb", "rgb24", 24,  "yuv", "yvyu422",  16, 1280, 720,   pixctrl_generic_rgb24_to_yvyu422, },
    { "rgb", "rgb24", 24,  "yuv", "uyvy422",  16, 1280, 720,   pixctrl_generic_rgb24_to_uyvy422, },
    { "rgb", "rgb24", 24,  "yuv", "vyuy422",  16, 1280, 720,   pixctrl_generic_rgb24_to_vyuy422, },
    { "rgb", "rgb24", 24,  "yuv", "nv12",     12, 1280, 720,   pixctrl_generic_rgb24_to_nv12,    },
    { "rgb", "rgb24", 24,  "yuv", "nv21",     12, 1280, 720,   pixctrl_generic_rgb24_to_nv21,    },
    { "rgb", "rgb24", 24,  "yuv", "yuv444p",  24, 1280, 720,   pixctrl_generic_rgb24_to_yuv444p, },
    { "rgb", "rgb24", 24,  "yuv", "yuv422p",  16, 1280, 720,   pixctrl_generic_rgb24_to_yuv422p, },
    { "rgb", "rgb24", 24,  "yuv", "yuv420p",  12, 1280, 720,   pixctrl_generic_rgb24_to_yuv420p, },

    { "rgb", "bgr24", 24,  "yuv", "yuv444",   24, 1280, 720,   pixctrl_generic_bgr24_to_yuv444,  },
    { "rgb", "bgr24", 24,  "yuv", "yuyv422",  16, 1280, 720,   pixctrl_generic_bgr24_to_yuyv422, },
    { "rgb", "bgr24", 24,  "yuv", "yvyu422",  16, 1280, 720,   pixctrl_generic_bgr24_to_yvyu422, },
    { "rgb", "bgr24", 24,  "yuv", "uyvy422",  16, 1280, 720,   pixctrl_generic_bgr24_to_uyvy422, },
    { "rgb", "bgr24", 24,  "yuv", "vyuy422",  16, 1280, 720,   pixctrl_generic_bgr24_to_vyuy422, },
    { "rgb", "bgr24", 24,  "yuv", "nv12",     12, 1280, 720,   pixctrl_generic_bgr24_to_nv12,    },
    { "rgb", "bgr24", 24,  "yuv", "nv21",     12, 1280, 720,   pixctrl_generic_bgr24_to_nv21,    },
    { "rgb", "bgr24", 24,  "yuv", "yuv444p",  24, 1280, 720,   pixctrl_generic_bgr24_to_yuv444p, },
    { "rgb", "bgr24", 24,  "yuv", "yuv422p",  16, 1280, 720,   pixctrl_generic_bgr24_to_yuv422p, },
    { "rgb", "bgr24", 24,  "yuv", "yuv420p",  12, 1280, 720,   pixctrl_generic_bgr24_to_yuv420p, },
};

void test_rgb2yuv_convert(char *dirpath)
{
    int32_t i, test_vectors = (int32_t)(sizeof(gsc_rgb2yuv_test_vector) / sizeof(rgb2yuv_test_vector_t));
    int32_t width, height;

    char resource_path[MAX_PATH_LEN];
    size_t src_len, expected_src_len;
    uint8_t *src;
    char *src_filename;

    char result_path[MAX_PATH_LEN];
    char *result_path_dir;
    uint8_t *dst;
    char *dst_filename;
    size_t dst_len;

    test_timestamp_t start, end;

    puts("###########################################################");
    puts("                TEST RGB to YUV Convert");
    puts("###########################################################");

    for (i = 0; i < test_vectors; ++i)
    {
        width = gsc_rgb2yuv_test_vector[i].width;
        height = gsc_rgb2yuv_test_vector[i].height;
        (void)sprintf(resource_path, "%s/resource/%s/%s-%dx%d.raw", 
                                     dirpath, gsc_rgb2yuv_test_vector[i].src_group,
                                     gsc_rgb2yuv_test_vector[i].src_fmt,
                                     width,
                                     height);
        (void)sprintf(result_path, "%s/result/%s/cvt_%s-%dx%d_from_%s.raw", 
                                    dirpath, gsc_rgb2yuv_test_vector[i].dst_group,
                                    gsc_rgb2yuv_test_vector[i].dst_fmt,
                                    width,
                                    height,
                                    gsc_rgb2yuv_test_vector[i].src_fmt);
        src_filename = get_filename(resource_path);
        dst_filename = get_filename(result_path);

        printf("[%2d / %2d] %-24s to %-36s ... ", i + 1, test_vectors, src_filename, dst_filename);
        free(src_filename);
        free(dst_filename);

        result_path_dir = get_dirpath(result_path);
        create_directory(result_path_dir);
        free(result_path_dir);

        src = load_rawdata(resource_path, &src_len);
        assert(src != NULL);

        expected_src_len = (((size_t)gsc_rgb2yuv_test_vector[i].width * gsc_rgb2yuv_test_vector[i].src_bpp) / 8) * (size_t)gsc_rgb2yuv_test_vector[i].height;
        assert(src_len == expected_src_len);

        dst_len = (((size_t)gsc_rgb2yuv_test_vector[i].width * gsc_rgb2yuv_test_vector[i].src_bpp) / 8) * (size_t)gsc_rgb2yuv_test_vector[i].height;
        dst = (uint8_t *)malloc(dst_len);
        assert(dst != NULL);

        get_timestamp(&start);
        gsc_rgb2yuv_test_vector[i].entry(src, dst, width, height);
        get_timestamp(&end);

        save_data_as_file(result_path, dst, dst_len);

        free(src);
        free(dst);

        printf("%zu.%09zu [sec]\n", end.sec - start.sec, end.nsec - start.nsec);
    }
}
