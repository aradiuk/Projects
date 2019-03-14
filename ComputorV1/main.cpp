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
		computor.ProcessEquation();
	} catch (const std::out_of_range &e) {
		std::cout << "Your input caused 'out of range' exception. Change it! \n";
	} catch (char const *str) {
	    std::cout << str << std::endl;
	} catch (const std::string &str) {
	    std::cout << str << std::endl;
	} catch (const std::exception &e) {
		std::cout << "Your input caused exception: " << e.what() << std::endl;
	}

	return 0;
}
