//
// Created by aradiuk on 8/18/2018.
//

#ifndef ABSTRACTVM_LEXER_HPP
#define ABSTRACTVM_LEXER_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <regex>

class Lexer {
    public:
        std::vector<std::string> StdInput();
        std::vector<std::string> FileInput(std::string filename);
};


#endif //ABSTRACTVM_LEXER_HPP
