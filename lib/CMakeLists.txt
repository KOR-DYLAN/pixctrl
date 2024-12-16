cmake_minimum_required(VERSION 3.22.1)
project(pixctrl VERSION 1.0.0 LANGUAGES ASM C)

# include
list(APPEND INC ${CMAKE_SOURCE_DIR}/include)

# source
list(APPEND SRC dummy.c)

# library target
add_library(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${INC})
