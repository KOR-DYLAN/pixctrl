cmake_minimum_required(VERSION 3.22.1)
project(sample VERSION 1.0.0 LANGUAGES ASM C)

# source
list(APPEND src main.c)

# target
add_executable(${PROJECT_NAME} ${src})
