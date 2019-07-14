#include "Body.hpp"

std::string Body::getName() const {
	return name;
}

double Body::getMass() const {
	return mass;
}

double Body::getRadius() const {
	return radius;
}

bool Body::isKeplerian() const {
	return keplerian;
}

double Body::getSMA() const {
	return sma;
}

double Body::getECC() const {
	return ecc;
}

double Body::getINC() const {
	return inc;
}

double Body::getLAN() const {
	return lan;
}

double Body::getAPE() const {
	return ape;
}

double Body::getTAE() const {
	return tae;
}

double Body::getEpoch() const {
	return epch;
}

Body* Body::getCenter() const {
	return center;
}

State* Body::getInitialState() const {
	return stateVectors;
}

std::string Body::to_string() const {
	//TODO: what if planet is non-keplerian

	if (keplerian) {
		return Body::name
			+ std::string("mass: ")
			+ std::to_string(mass) + std::string("\n")
			+ std::string("radius: ")
			+ std::to_string(radius) + std::string("\n")
			+ std::string("semi-major axis: ")
			+ std::to_string(Body::sma) + std::string("\n")
			+ std::string("inclination: ")
			+ std::to_string(Body::inc) + std::string("\n")
			+ std::string("longitude of ascending node: ")
			+ std::to_string(Body::lan) + std::string("\n")
			+ std::string("argument of periapsis: ")
			+ std::to_string(Body::ape) + std::string("\n")
			+ std::string("true anomaly at epoch: ")
			+ std::to_string(Body::tae) + std::string("\n")
			+ std::string("epoch: ")
			+ std::to_string(Body::epch) + std::string("\n")
		;
	} else {
		return Body::name
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
			+ std::to_string(Body::epch) + std::string("\n")
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

bool operator!=(const Body& Body1, const Body& Body2) {
	return !(Body1 == Body2);
}