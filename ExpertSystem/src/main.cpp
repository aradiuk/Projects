#include "ExpertSystem.hpp"

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "Hey, you forgot an input file!" << std::endl;
        return 1;
    } else if (argc > 2) {
        std::cout << "Too many input arguments! Slow down!" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    std::ifstream ifs(fileName.c_str());
    if (!ifs.good()) {
        std::cout << "Couldn't open your file. Try another one." << std::endl;
        return 1;
    }

    try {
        ExpertSystem expertSystem;
        expertSystem.StartEngine(fileName);
    } catch (const std::string &ex) {
        std::cout << std::endl << ex << std::endl;
    } catch (const char *ex) {
        std::cout << std::endl << ex << std::endl;
    } catch (const std::exception &ex) {
        std::cout << std::endl << ex.what() << std::endl;
    }

	return 0;
}
