cmake_minimum_required(VERSION 3.12)
project(AbstractVM)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AbstractVM
        Exception.cpp
        Exception.hpp
        IOperand.hpp
        main.cpp
        Operand.hpp
        OperandFactory.cpp
        OperandFactory.hpp Lexer.cpp Lexer.hpp Parser.cpp Parser.hpp)
