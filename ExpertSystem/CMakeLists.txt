cmake_minimum_required(VERSION 3.13)
project(ExpertSystem)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(cmake-build-debug)

add_executable(ExpertSystem
        ExpertSystem.cpp
        ExpertSystem.hpp
        Lexer.cpp
        Lexer.hpp
        main.cpp
        Parser.cpp
        Parser.hpp
        Validator.cpp
        Validator.hpp)
