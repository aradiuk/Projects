#include "Lexer.hpp"
#include "Parser.hpp"

int main(int argc, char **argv)
{
    if (argc > 2) {
        std::cout << "Too many arguments.\n";
        return -1;
    }
    Lexer lexer_;
    Parser parser_;

    if (argc == 1) {
        parser_.ReadData(lexer_.StdInput());
    } else {
        parser_.ReadData(lexer_.FileInput(argv[1]));
    }
    return 0;
}


