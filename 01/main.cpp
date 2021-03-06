#include "main.h"

#include <iostream>

int main(int argc, char** argv) {
	if (argc <= 1) {
		std::cerr << "Usage : " << argv[0] << " '5 + 5'" << std::endl;
		return -1;
	}

	std::string str = argv[1];

	if (!CheckString(str)) {
		std::cerr << "ERROR : Invalid expression syntax" << std::endl;
		return -2;
	}
	try {
		DeleteSpaces(str);
		SimplifyMinuses(str);
		std::cout << ParseArithmeticEspression(str) << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "ERROR : " << "Exception was handled during runtime ( " << e.what() << " )" << std::endl;
		return -3;
	}
	return 0;
}
