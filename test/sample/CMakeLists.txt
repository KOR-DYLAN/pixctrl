cmake_minimum_required(VERSION 3.22.1)
project(sample VERSION 1.0.0 LANGUAGES ASM C)

# include
list(APPEND INC ${CMAKE_SOURCE_DIR}/include)

# source
list(APPEND SRC main.c)

# library
list(APPEND LIBROOT ${CMAKE_SOURCE_DIR}/output/lib/${CMAKE_SYSTEM_PROCESSOR})
list(APPEND LIBS pixctrl)

# target
add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${INC})
target_link_directories(${PROJECT_NAME} PRIVATE ${LIBROOT})
target_link_libraries(${PROJECT_NAME} ${LIBS})
