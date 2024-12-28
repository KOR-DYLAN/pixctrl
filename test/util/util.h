#ifndef __UTIL__H__
#define __UTIL__H__

#define MAX_PATH_LEN    (512)
#define MAX_FILENAME    (128)

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

typedef struct {
    size_t sec;
    size_t nsec;
} test_timestamp_t;

extern char *get_input_image_path(int argc, char *argv[]);
extern const char * get_format_as_string(test_image_format_t fmt);
extern test_result_t save_data_as_file(char *path, uint8_t *buf, size_t len);
extern test_result_t load_png_to_test_image(char *path, test_image_t *img);
extern uint8_t *load_rawdata(char *path, size_t *rawdata_len);
extern test_result_t save_test_image_as_rawdata(const char *rootpath, const char *prefix, uint8_t *buf, int32_t width, int32_t height, size_t len);
extern test_result_t create_directory(const char *path);
extern char *get_dirpath(const char *path);
extern char *get_filename(const char *path);
extern void get_timestamp(test_timestamp_t *timestamp);


#endif  //!__UTIL__H__