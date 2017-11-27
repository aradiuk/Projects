cmake_minimum_required(VERSION 3.5.1)
project(Timeit)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        main.c)

add_executable(timeit ${SOURCE_FILES})
