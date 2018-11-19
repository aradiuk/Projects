#include "ComputorV1.hpp"

int main(int argc, char **argv) {

	if (argc < 2) {
		std::cout << "No equation - no output.\n";
		return 1;
	} else if (argc > 2) {
		std::cout << "Woah! One equation at a time, please! I am just a machine!\n";
		return 1;
	}

	ComputorV1 computor(argv[1]);
	try {
		computor.processEquation();
	} catch (std::out_of_range &e) {
		std::cout << "Your input caused 'out of range' exception.\n";
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}


	return 0;
}