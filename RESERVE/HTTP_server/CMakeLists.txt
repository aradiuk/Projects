cmake_minimum_required(VERSION 2.6)
project(http_server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -Werror -Wextra -Wall")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/includes /usr/include/libxml2)

set(SOURCE_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/Request.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/Response.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/parse_config.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/parse_request.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/includes/Server.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/includes/http.hpp)

add_executable(http_server ${SOURCE_FILES})
target_link_libraries(http_server -lxml2 -pthread)
