#include "System.hpp"

int System::findBodyIndex(Body body) {
    int i;
    for (i = 0; i < (int) bodies.size() && bodies[i] != body; i++);
    return i;
}

void System::addBody(Body body) {
    bodies.push_back(body);
}

void System::removeBody(Body body) {
    int i = findBodyIndex(body);
    if (bodies[i] == body) {
        return;
    }
    bodies.erase(bodies.begin() + (std::vector<Body>::size_type) i);
}

void System::addThruster(Body body, Thruster thruster) {
    int i = findBodyIndex(body);
    if (bodies[i] != body) {
        return;
    }
    std::pair<Body, Thruster> pair = {body, thruster};
    thrusters.insert(pair);
}

void System::removeThruster(Body body) {
    int i = findBodyIndex(body);
    if (bodies[i] != body) {
        return;
    }
    thrusters.erase(body);
}

bool System::hasThruster(Body body) {
    std::map<Body, Thruster>::const_iterator thrstItr
        = thrusters.find(body);
    if (thrstItr == thrusters.end()) {
        return false;
    } else {
        return true;
    }
}

Thruster System::getThruster(Body body) {
    std::map<Body, Thruster>::const_iterator thrstItr
        = thrusters.find(body);
    if (thrstItr == thrusters.end()) {
        return Thruster(0,0,0);
    } else {
        return thrstItr->second;
    }
}

std::vector<Body> System::getBodies() {
    return std::vector<Body>(bodies);
}