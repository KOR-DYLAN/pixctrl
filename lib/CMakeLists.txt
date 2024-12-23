cmake_minimum_required(VERSION 3.22.1)
project(pixctrl VERSION 1.0.0 LANGUAGES ASM C)

include(common/CMakeLists.txt)
include(generic/convert/CMakeLists.txt)
include(generic/mixer/CMakeLists.txt)
include(generic/resize/CMakeLists.txt)

# include
list(APPEND INC ${CMAKE_SOURCE_DIR}/include)
list(APPEND INC ${CMAKE_CURRENT_LIST_DIR})

# source
# list(APPEND SRC dummy.c)

# library target
add_library(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${INC})
