cmake_minimum_required(VERSION 3.22.1)
project(util VERSION 1.0.0 LANGUAGES ASM C)

# load PkgConfig
find_package(PkgConfig REQUIRED)

# find cairo package
pkg_check_modules(CAIRO REQUIRED cairo)

# packages
find_package(Cairo)

# macro
list(APPEND DEFINES DEFAULT_INPUT_IMAGE_PATH="${CMAKE_SOURCE_DIR}/resource/sample.png")

# include
list(APPEND INC ${CAIRO_INCLUDE_DIRS})

# source
list(APPEND SRC util.c)

# library root
list(APPEND LIBROOT ${CAIRO_LIBRARY_DIRS})

# library
list(APPEND LIBS ${CAIRO_LIBRARIES})

# target
add_library(${PROJECT_NAME} ${SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${DEFINES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INC})
target_link_directories(${PROJECT_NAME} PRIVATE ${LIBROOT})
target_link_libraries(${PROJECT_NAME} ${LIBS})
