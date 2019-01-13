#include "Planet.hpp"

std::string Planet::to_string() {
	return Planet::name + std::string("semi-major axis") + std::to_string(Planet::sma)
		+ std::string("inclination") + std::to_string(Planet::inc)
		+ std::string("longitude of ascending node") + std::to_string(Planet::lan)
		+ std::string("argument of periapsis") + std::to_string(Planet::ape)
		+ std::string("true anomaly at epoch") + std::to_string(Planet::tae)
		+ std::string("epoch") + std::to_string(Planet::epch);
}
