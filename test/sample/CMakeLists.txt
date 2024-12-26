cmake_minimum_required(VERSION 3.22.1)
project(sample VERSION 1.0.0 LANGUAGES ASM C)

# macro
# list(APPEND DEFINES )

# include
list(APPEND INC ${CMAKE_SOURCE_DIR}/include)
list(APPEND INC ${CMAKE_CURRENT_LIST_DIR}/../util)

# source
list(APPEND SRC main.c)
list(APPEND SRC rgb2rgb.c)
list(APPEND SRC rgb2yuv.c)

# library root
list(APPEND LIBROOT ${CMAKE_SOURCE_DIR}/output/lib/${CMAKE_SYSTEM_PROCESSOR})

# library
list(APPEND LIBS util)
list(APPEND LIBS pixctrl)

# target
add_executable(${PROJECT_NAME} ${SRC})
# target_compile_definitions(${PROJECT_NAME} PRIVATE ${DEFINES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INC})
target_link_directories(${PROJECT_NAME} PRIVATE ${LIBROOT})
target_link_libraries(${PROJECT_NAME} ${LIBS})
