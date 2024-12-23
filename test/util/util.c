#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <cairo.h>
#include "util.h"

#define MAX_PATH_LEN    (512)
#define MAX_FILENAME    (128)


char *get_input_image_path(int argc, char *argv[])
{
    static char shared_path[MAX_PATH_LEN];
    char *input_image_path = shared_path;

    switch (argc) {
    case 1:
        (void)strcpy(shared_path, DEFAULT_INPUT_IMAGE_PATH);
        break;

    case 2:
        (void)strcpy(shared_path, argv[1]);
        break;
    
    default:
        input_image_path = NULL;
        break;
    }

    return input_image_path;
}

const char * get_format_as_string(test_image_format_t fmt)
{
    const char *ffmpeg_style_fmt = NULL;

    switch (fmt) {
    case TEST_IMG_FMT_RGBA32:
        ffmpeg_style_fmt = "bgra";
        break;
    case TEST_IMG_FMT_RGBX32:
        ffmpeg_style_fmt = "bgra";
        break;
    default:
        ffmpeg_style_fmt = "unknown";
        break;
    }

    return ffmpeg_style_fmt;
}

test_result_t save_data_as_file(char *path, uint8_t *buf, size_t len)
{
    test_result_t result = TEST_RESULT_FAILED;
    FILE *fp;

    fp = fopen(path, "wb");
    if (fp != NULL)
    {
        (void)fwrite(buf, len, 1, fp);
        fclose(fp);

        result = TEST_RESULT_SUCCESS;
    }

    return result;
}

test_result_t load_png_to_test_image(char *path, test_image_t *img)
{
    test_result_t result = TEST_RESULT_FAILED;
    cairo_status_t status;
    cairo_surface_t *img_surface;
    size_t len;

    if ((path != NULL) && (img != NULL))
    {
        img_surface = cairo_image_surface_create_from_png(path);
        status = cairo_surface_status(img_surface);
        if ((img_surface != NULL) && (status == CAIRO_STATUS_SUCCESS))
        {
            img->width = cairo_image_surface_get_width(img_surface);
            img->height = cairo_image_surface_get_height(img_surface);
            img->stride = cairo_image_surface_get_stride(img_surface);
            switch (cairo_image_surface_get_format(img_surface)) {
            case CAIRO_FORMAT_ARGB32:
                img->fmt = TEST_IMG_FMT_RGBA32;
                break;
            case CAIRO_FORMAT_RGB24:
                img->fmt = TEST_IMG_FMT_RGBX32;
                break;
            default:
                img->fmt = TEST_IMG_FMT_UNKNOWN;
                break;
            }

            if ((0 < img->width) && (0 < img->height) &&
                (img->width <= img->stride) && (img->fmt != TEST_IMG_FMT_UNKNOWN))
            {
                len = (size_t)img->stride * (size_t)img->height;
                img->buf = (uint8_t *)malloc(len);
                if (img->buf != NULL)
                {
                    (void)memcpy(img->buf, cairo_image_surface_get_data(img_surface), len);
                    result = TEST_RESULT_SUCCESS;
                }
                else
                {
                    (void)memset(img, 0, sizeof(test_image_t));
                }
            }
            else
            {
                (void)memset(img, 0, sizeof(test_image_t));
            }
        }
        cairo_surface_destroy(img_surface);
    }

    return result;
}

test_result_t save_test_image_as_rawdata(const char *rootpath, const char *prefix, test_image_t *img)
{
    test_result_t result;
    char destpath[MAX_PATH_LEN];
    char *pos = destpath;

    /* make path */
    if (rootpath != NULL)
    {
        pos += sprintf(pos, "%s/", rootpath);
    }
    if (prefix != NULL)
    {
        pos += sprintf(pos, "%s_", prefix);
    }
    (void)sprintf(pos, "%dx%d.raw", img->width, img->height);

    result = save_data_as_file(destpath, img->buf, (size_t)img->stride * (size_t)img->height);
    return result;
}
