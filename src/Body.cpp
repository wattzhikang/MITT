#include "Body.hpp"

std::string Body::getName() {
	return name;
}

double Body::getMass() {
	return mass;
}

double Body::getRadius() {
	return radius;
}

bool Body::isKeplerian() {
	return keplerian;
}

double Body::getSMA() {
	return sma;
}

double Body::getECC() {
	return ecc;
}

double Body::getLAN() {
	return lan;
}

double Body::getAPE() {
	return ape;
}

double Body::getTAE() {
	return tae;
}

double Body::getEpoch() {
	return epch;
}

Body* Body::getCenter() {
	return center;
}

State* Body::getInitialState() {
	return stateVectors;
}

std::string Planet::to_string() {
	//TODO: what if planet is non-keplerian

	if (keplerian) {
		return Planet::name +
			+ std::string("mass: ")
			+ std::to_string(mass) + std::string("\n")
			+ std::string("radius: ")
			+ std::to_string(radius) + std::string("\n")
			+ std::string("semi-major axis: ")
			+ std::to_string(Planet::sma) + std::string("\n")
			+ std::string("inclination: ")
			+ std::to_string(Planet::inc) + std::string("\n")
			+ std::string("longitude of ascending node: ")
			+ std::to_string(Planet::lan) + std::string("\n")
			+ std::string("argument of periapsis: ")
			+ std::to_string(Planet::ape) + std::string("\n")
			+ std::string("true anomaly at epoch: ")
			+ std::to_string(Planet::tae) + std::string("\n")
			+ std::string("epoch: ")
			+ std::to_string(Planet::epch) + std::string("\n")
		;
	} else {
		return Planet::name +
			+ std::string("mass: ")
			+ std::to_string(mass) + std::string("\n")
			+ std::string("radius: ")
			+ std::to_string(radius) + std::string("\n")
			+ std::string("X Position")
			+ std::to_string(stateVectors->getXPosition()) + std::string("\n")
			+ std::string("Y Position")
			+ std::to_string(stateVectors->getYPosition()) + std::string("\n")
			+ std::string("Z Position")
			+ std::to_string(stateVectors->getZPosition()) + std::string("\n")
			+ std::string("X Velocity")
			+ std::to_string(stateVectors->getXVelocity()) + std::string("\n")
			+ std::string("Y Velocity")
			+ std::to_string(stateVectors->getYVelocity()) + std::string("\n")
			+ std::string("Z Velocity")
			+ std::to_string(stateVectors->getZVelocity()) + std::string("\n")
			+ std::string("epoch: ")
			+ std::to_string(Planet::epch) + std::string("\n")
		;
	}
}

bool operator==(const Body& Body1, const Body& Body2) {
	if (Body1.getName() != Body2.getName()) {
		return false;
	} else {
		return true;
	}
}