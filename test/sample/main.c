#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "util.h"
#include "pixctrl.h"
#include "test_vector.h"

int32_t main(int32_t argc, char *argv[])
{
    int32_t ret = 0;
    test_result_t result;
    test_image_t img;

    result = load_png_to_test_image(get_input_image_path(argc, argv), &img);
    if (result == TEST_RESULT_SUCCESS)
    {
        test_rgb2rgb_convert(&img);
    }
    else
    {
        fprintf(stderr, "can not load image...\n");
        ret = -1;
    }

    return ret;
}
