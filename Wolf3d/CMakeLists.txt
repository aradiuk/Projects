cmake_minimum_required(VERSION 3.12)
project(Wolf3d C)

set(CMAKE_C_STANDARD 99)

include_directories(libft/includes, includes, src)

add_executable(Wolf3d src/main.c libft/includes/libft.h src/keyhooks.c src/map_reading.c includes/wolf3d.h src/environment.c src/raycasting.c)