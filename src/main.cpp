#include <iostream>

#include "Planet.hpp"
#include "FileReader.hpp"

int main() {
	std::cout << "Hello, world!" << std::endl;

	std::cout << file_to_string(std::string("config/test_system"));
}
