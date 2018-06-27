/*
 * main.cpp
 *
 *  Created on: Jun 27, 2018
 *      Author: aradiuk
 */
#include "AbstractVM.hpp"

int main(int argc, char **argv)
{
    if (argc > 2) {
        std::cout << "Too many arguments.\n";
        return -1;
    }

    AbstractVM vm;

    vm.start(argc, argv);

    return 0;
}


