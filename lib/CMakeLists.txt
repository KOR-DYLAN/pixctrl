cmake_minimum_required(VERSION 3.22.1)
project(nc_graphics VERSION 1.0.0 LANGUAGES ASM C)

# include
list(APPEND INC ${CMAKE_SOURCE_DIR}/include)


# core
list(APPEND SRC dummy.c)

# library target
add_library(${CMAKE_PROJECT_NAME} ${SRC})
