#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "pixctrl.h"
#include "test_vector.h"

typedef pixctrl_result_t(*yuv2yuv_vector_entry_t)(uint8_t *src, uint8_t *dst, int32_t width, int32_t height);

typedef struct {
    const char *src_group;
    const char *src_fmt;
    size_t src_bpp;

    const char *dst_group;
    const char *dst_fmt;
    size_t dst_bpp;

    int32_t width;
    int32_t height;

    yuv2yuv_vector_entry_t entry;
} yuv2yuv_test_vector_t;

static const yuv2yuv_test_vector_t gsc_yuv2yuv_test_vector[] = {
    /* src   src        src  dst        dst         dst
       group fmt        bpp  group      fmt         bpp width height converter */
    { "yuv", "yuv444",  24,  "yuv2yuv", "yuyv422",  16, 1280, 720,   pixctrl_generic_yuv444_to_yuyv422,   },
    { "yuv", "yuv444",  24,  "yuv2yuv", "yvyu422",  16, 1280, 720,   pixctrl_generic_yuv444_to_yvyu422,   },
    { "yuv", "yuv444",  24,  "yuv2yuv", "uyvy422",  16, 1280, 720,   pixctrl_generic_yuv444_to_uyvy422,   },
    { "yuv", "yuv444",  24,  "yuv2yuv", "vyuy422",  16, 1280, 720,   pixctrl_generic_yuv444_to_vyuy422,   },
    { "yuv", "yuv444",  24,  "yuv2yuv", "nv12",     12, 1280, 720,   pixctrl_generic_yuv444_to_nv12,      },
    { "yuv", "yuv444",  24,  "yuv2yuv", "nv21",     12, 1280, 720,   pixctrl_generic_yuv444_to_nv21,      },

    { "yuv", "yuyv422", 16,  "yuv2yuv", "yuv444",   24, 1280, 720,   pixctrl_generic_yuyv422_to_yuv444,   },
    { "yuv", "yvyu422", 16,  "yuv2yuv", "yuv444",   24, 1280, 720,   pixctrl_generic_yvyu422_to_yuv444,   },
    { "yuv", "uyvy422", 16,  "yuv2yuv", "yuv444",   24, 1280, 720,   pixctrl_generic_uyvy422_to_yuv444,   },
    { "yuv", "vyuy422", 16,  "yuv2yuv", "yuv444",   24, 1280, 720,   pixctrl_generic_vyuy422_to_yuv444,   },

    { "yuv", "yuyv422", 16,  "yuv2yuv", "nv12",     12, 1280, 720,   pixctrl_generic_yuyv422_to_nv12,     },
    { "yuv", "yvyu422", 16,  "yuv2yuv", "nv12",     12, 1280, 720,   pixctrl_generic_yvyu422_to_nv12,     },
    { "yuv", "uyvy422", 16,  "yuv2yuv", "nv12",     12, 1280, 720,   pixctrl_generic_uyvy422_to_nv12,     },
    { "yuv", "vyuy422", 16,  "yuv2yuv", "nv12",     12, 1280, 720,   pixctrl_generic_vyuy422_to_nv12,     },

    { "yuv", "yuyv422", 16,  "yuv2yuv", "nv21",     12, 1280, 720,   pixctrl_generic_yuyv422_to_nv21,     },
    { "yuv", "yvyu422", 16,  "yuv2yuv", "nv21",     12, 1280, 720,   pixctrl_generic_yvyu422_to_nv21,     },
    { "yuv", "uyvy422", 16,  "yuv2yuv", "nv21",     12, 1280, 720,   pixctrl_generic_uyvy422_to_nv21,     },
    { "yuv", "vyuy422", 16,  "yuv2yuv", "nv21",     12, 1280, 720,   pixctrl_generic_vyuy422_to_nv21,     },

    { "yuv", "nv12",   12,  "yuv2yuv", "yuv444",    24, 1280, 720,   pixctrl_generic_nv12_to_yuv444,     },
    { "yuv", "nv21",   12,  "yuv2yuv", "yuv444",    24, 1280, 720,   pixctrl_generic_nv21_to_yuv444,     },

    { "yuv", "nv12",   12,  "yuv2yuv", "yuyv422",   16, 1280, 720,   pixctrl_generic_nv12_to_yuyv422,     },
    { "yuv", "nv12",   12,  "yuv2yuv", "yvyu422",   16, 1280, 720,   pixctrl_generic_nv12_to_yvyu422,     },
    { "yuv", "nv12",   12,  "yuv2yuv", "uyvy422",   16, 1280, 720,   pixctrl_generic_nv12_to_uyvy422,     },
    { "yuv", "nv12",   12,  "yuv2yuv", "vyuy422",   16, 1280, 720,   pixctrl_generic_nv12_to_vyuy422,     },

    { "yuv", "nv21",   12,  "yuv2yuv", "yuyv422",   16, 1280, 720,   pixctrl_generic_nv21_to_yuyv422,     },
    { "yuv", "nv21",   12,  "yuv2yuv", "yvyu422",   16, 1280, 720,   pixctrl_generic_nv21_to_yvyu422,     },
    { "yuv", "nv21",   12,  "yuv2yuv", "uyvy422",   16, 1280, 720,   pixctrl_generic_nv21_to_uyvy422,     },
    { "yuv", "nv21",   12,  "yuv2yuv", "vyuy422",   16, 1280, 720,   pixctrl_generic_nv21_to_vyuy422,     },

    { "yuv", "yuv444", 24,  "yuv2yuv", "yuv444p",   24, 1280, 720,   pixctrl_generic_yuv444_to_yuv444p,   },
    { "yuv", "yuv444", 24,  "yuv2yuv", "yuv422p",   16, 1280, 720,   pixctrl_generic_yuv444_to_yuv422p,   },
    { "yuv", "yuv444", 24,  "yuv2yuv", "yuv420p",   12, 1280, 720,   pixctrl_generic_yuv444_to_yuv420p,   },
};

void test_yuv2yuv_convert(char *dirpath)
{
    int32_t i, test_vectors = (int32_t)(sizeof(gsc_yuv2yuv_test_vector) / sizeof(yuv2yuv_test_vector_t));
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
    puts("                TEST YUV to YUV Convert");
    puts("###########################################################");

    for (i = 0; i < test_vectors; ++i)
    {
        width = gsc_yuv2yuv_test_vector[i].width;
        height = gsc_yuv2yuv_test_vector[i].height;
        (void)sprintf(resource_path, "%s/resource/%s/%s-%dx%d.raw", 
                                     dirpath, gsc_yuv2yuv_test_vector[i].src_group,
                                     gsc_yuv2yuv_test_vector[i].src_fmt,
                                     width,
                                     height);
        (void)sprintf(result_path, "%s/result/%s/cvt_%s-%dx%d_from_%s.raw", 
                                    dirpath, gsc_yuv2yuv_test_vector[i].dst_group,
                                    gsc_yuv2yuv_test_vector[i].dst_fmt,
                                    width,
                                    height,
                                    gsc_yuv2yuv_test_vector[i].src_fmt);
        src_filename = get_filename(resource_path);
        dst_filename = get_filename(result_path);

        printf("[%2d / %2d] %-24s to %-36s ... ", i + 1, test_vectors, src_filename, dst_filename);
        fflush(stdout);
        free(src_filename);
        free(dst_filename);

        result_path_dir = get_dirpath(result_path);
        create_directory(result_path_dir);
        free(result_path_dir);

        src = load_rawdata(resource_path, &src_len);
        assert(src != NULL);

        expected_src_len = (((size_t)gsc_yuv2yuv_test_vector[i].width * gsc_yuv2yuv_test_vector[i].src_bpp) / 8) * (size_t)gsc_yuv2yuv_test_vector[i].height;
        assert(src_len == expected_src_len);

        dst_len = (((size_t)gsc_yuv2yuv_test_vector[i].width * gsc_yuv2yuv_test_vector[i].dst_bpp) / 8) * (size_t)gsc_yuv2yuv_test_vector[i].height;
        dst = (uint8_t *)malloc(dst_len);
        assert(dst != NULL);

        get_timestamp(&start);
        gsc_yuv2yuv_test_vector[i].entry(src, dst, width, height);
        get_timestamp(&end);

        save_data_as_file(result_path, dst, dst_len);

        free(src);
        free(dst);

        printf("%zu.%09zu [sec]\n", end.sec - start.sec, end.nsec - start.nsec);
    }
}
