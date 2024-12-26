#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <sys/stat.h>
#include <errno.h>
#include "util.h"

#define SEPERATOR   '/'

test_result_t create_directory(const char *path)
{
    test_result_t result = TEST_RESULT_SUCCESS;
    const char *pos = NULL;
    char *dirname = NULL;

    dirname = (char *)calloc(1, strlen(path) + 1);
    assert(dirname != NULL);

    pos = strchr(path, SEPERATOR);
    while (pos != NULL)
    {
        if ((pos != path) && (*(pos - 1) == SEPERATOR))
        {
            pos = strchr(++pos, SEPERATOR);
            continue;
        }

        (void)memcpy(dirname, path, pos - path);
        dirname[pos - path] = '\0';
        pos = strchr(++pos, SEPERATOR);

        if (mkdir(dirname, 0744) != 0)
        {
            if (errno != EEXIST)
            {
                result = TEST_RESULT_FAILED;
                break;
            }
        }
    }

    return result;
}
