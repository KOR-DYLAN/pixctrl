#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "util.h"
#include "pixctrl.h"

int32_t main(int32_t argc, char *argv[])
{
    int32_t ret = 0;
    test_result_t result;
    test_image_t img;

    result = load_png_to_test_image(get_input_image_path(argc, argv), &img);
    if (result == TEST_RESULT_SUCCESS)
    {
        save_test_image_as_rawdata(NULL, "test", &img);
    }
    else
    {
        fprintf(stderr, "can not load image...\n");
        ret = -1;
    }

    return ret;
}
