cmake_minimum_required(VERSION 3.13)
project(PSU_2018_malloc)

set(CMAKE_C_STANDARD 99)

include_directories(includes)

add_library(my_malloc SHARED
            sources/malloc.c
            rnb_trees/rnb_trees.c
            rnb_trees/violation.c)

add_executable(test test.c)
target_link_libraries(test my_malloc)