#include "AbstractVM.hpp"


void AbstractVM::start(int argc, char **argv) {
    if (argc == 1) {
        stdInput();
    } else if (argc == 2) {
        fileInput(argv[1]);
    }

    std::cout << "Started!\n";
}


