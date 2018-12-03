#include "Planet.hpp"

std::string Planet::to_string() {
	return Planet::name + std::to_string(Planet::sma) + std::to_string(Planet::inc)
		+ std::to_string(Planet::lan) + std::to_string(Planet::ape)
		+ std::to_string(Planet::tae) + std::to_string(Planet::epch);
}
