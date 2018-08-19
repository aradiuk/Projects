#include "Lexer.hpp"

std::vector<std::string> Lexer::FileInput(std::string filename) {
    std::string readLine;
    std::ifstream fileStream(filename.c_str());
    std::vector<std::string> commands;

    if (!fileStream.is_open() || fileStream.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "File is empty or there was a problem opening it.\n";
        exit(1);
    }

    while(std::getline(fileStream, readLine)) {
        if (readLine.empty()) {
            continue;
        }
        commands.push_back(readLine);
    }
    return (commands);
}

std::vector<std::string> Lexer::StdInput() {
    std::string readLine;
    std::vector<std::string> commands;

    while (std::cin) {
        std::getline(std::cin, readLine);
        if (readLine.empty()) {
            continue;
        }

        if (readLine == ";;") {
            break;
        }
        commands.push_back(readLine);
    }
    return (commands);
}