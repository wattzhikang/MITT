#include <iostream>

#include "FileReader.hpp"
#include "ConfigFile.hpp"

int main() {
	std::string configContent = file_to_string(
			std::string("config/test_system"));

	ConfigFile systemConfig(configContent);

	std::cout << systemConfig.to_string() << std::endl;
}
