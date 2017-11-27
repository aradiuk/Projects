cmake_minimum_required(VERSION 2.6)
project(tcp_chat)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -Werror -Wextra -Wall")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set(SOURCE_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/arguments.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/Server_control.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/User.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/includes/Server.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/includes/User.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/includes/Client.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/includes/tcp.hpp)

add_executable(tcp_chat ${SOURCE_FILES})
target_link_libraries(tcp_chat -pthread)
