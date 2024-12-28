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
    char *dirpath = get_dirpath(argv[0]);

    if (dirpath != NULL)
    {
        test_rgb2rgb_convert(dirpath);
        test_rgb2yuv_convert(dirpath);
    }
    else
    {
        ret = -1;
    }

    return ret;
}
