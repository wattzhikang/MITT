#include <iostream>

#include "FileReader.hpp"
#include "ConfigFile.hpp"
#include "Planet.hpp"

int main() {
	//read the config file containing the units
	std::string unitsContent = file_to_string(
		std::string("config/units")
	);
	ConfigFile unitConfig(unitsContent);

	//read the config file containing planets
	std::string configContent = file_to_string(
			std::string("config/test_system")
	);
	ConfigFile systemConfig(configContent);
	systemConfig.setUnits(unitConfig);

	std::vector<ConfigFile*> planetConfigs = systemConfig.getSections("object");
	std::vector<Planet*> planets;

	//this is how the system builder will eventually build planets
	for (ConfigFile* object : planetConfigs) {
		planets.push_back(
			new Planet(
				object->getToken("name"),
				object->getDistance("sma"),
				object->getDouble("ecc"),
				object->getAngle("inc"),
				object->getAngle("lan"),
				object->getAngle("ape"),
				object->getAngle("tae"),
				object->getDouble("epoch")
			)
		);
	}

	for (Planet* planet : planets) {
		std::cout << planet->to_string() << std::endl;
	}
}