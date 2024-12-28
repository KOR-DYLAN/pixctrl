#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include <time.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include "util.h"

static int32_t is_exist_directory(const char *path)
{
    int32_t result;
    struct stat info;

    /* Call stat to retrieve information about the directory */
    if (stat(path, &info) != 0)
    {
        /* stat failed, directory does not exist */
        result = -1;
    }
    else if (info.st_mode & S_IFDIR)
    {
        /* It's a directory */
        result = 0;
    }
    else
    {
        /* It's not a directory (could be a file or something else) */
        result = -2;
    }

    return result;
}

test_result_t create_directory(const char *path)
{
    test_result_t result = TEST_RESULT_SUCCESS;
    char *clone_path;
    char *target_path;
    char *it;
    char *dir;

    clone_path = (char *)malloc(strlen(path) + 1);
    assert(clone_path != NULL);

    target_path = (char *)malloc(strlen(path) + 1);
    assert(target_path != NULL);

    (void)strcpy(clone_path, path);

    if (memcmp(path, "/", 1) == 0)
    {
        memcpy(target_path, "/", 2);
        it = clone_path + 1;
    }
    else if (memcmp(path, "./", 2) == 0)
    {
        target_path[0] = '\0';
        it = clone_path + 2;
    }
    else
    {
        result = TEST_RESULT_FAILED;
        it = NULL;
    }

    for(dir = strsep(&it, "/"); dir != NULL; dir = strsep(&it, "/"))
    {
        if (*dir != '\0')
        {
            strcat(target_path, dir);

            if (is_exist_directory(target_path) != 0)
            {
                mkdir(target_path, S_IRWXU | S_IRWXG | (S_IROTH | S_IXOTH));
            }
            strcat(target_path, "/");
        }
    }
    

    return result;
}

char *get_dirpath(const char *path)
{
    char *temp;
    char *dirpath;

    temp = (char *)calloc(1, strlen(path) + 1);
    assert(temp != NULL);

    (void)strcpy(temp, path);

    dirpath = dirname(temp);
    if (dirpath == NULL)
    {
        free(temp);
        temp = NULL;
    }

    return dirpath;
}

char *get_filename(const char *path)
{
    char *clone_path;
    char *temp;
    char *filename;

    clone_path = (char *)malloc(strlen(path) + 1);
    assert(clone_path != NULL);
    (void)strcpy(clone_path, path);

    temp = basename(clone_path);
    if (temp != NULL)
    {
        filename = (char *)malloc(strlen(temp) + 1);
        assert(filename != NULL);

        (void)strcpy(filename, temp);
    }

    free(clone_path);

    return filename;
}

void get_timestamp(test_timestamp_t *timestamp)
{
    struct timespec ts;

    assert(timestamp != NULL);

    (void)clock_gettime(CLOCK_MONOTONIC, &ts);
    timestamp->sec = (size_t)ts.tv_sec;
    timestamp->nsec = (size_t)ts.tv_nsec;
}
