cmake_minimum_required(VERSION 3.22.1)
project(pixctrl VERSION 1.0.0)

# ouput
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib/${CMAKE_SYSTEM_PROCESSOR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib/${CMAKE_SYSTEM_PROCESSOR})

# copy resource
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resource DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# library target
add_subdirectory(lib)

# test target
add_subdirectory(test)
