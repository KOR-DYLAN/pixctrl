#ifndef __UTIL__H__
#define __UTIL__H__

typedef enum {
    TEST_RESULT_FAILED = -1,
    TEST_RESULT_SUCCESS = 0,
} test_result_t;

typedef enum {
   TEST_IMG_FMT_RGBA32, 
   TEST_IMG_FMT_RGBX32, 
   TEST_IMG_FMT_UNKNOWN, 
   MAX_OF_TEST_IMG_FMT, 
} test_image_format_t;

typedef struct {
    test_image_format_t fmt;
    uint8_t *buf;
    int32_t width;
    int32_t height;
    int32_t stride;
} test_image_t;

extern char *get_input_image_path(int argc, char *argv[]);
extern const char * get_format_as_string(test_image_format_t fmt);
extern test_result_t save_data_as_file(char *path, uint8_t *buf, size_t len);
extern test_result_t load_png_to_test_image(char *path, test_image_t *img);
extern test_result_t save_test_image_as_rawdata(const char *rootpath, const char *prefix, uint8_t *buf, int32_t width, int32_t height, size_t len);

#endif  //!__UTIL__H__