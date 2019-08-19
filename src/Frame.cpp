#include "Frame.hpp"

State Frame::getPosition(const Body& planet) {
    std::map<Body, State>::iterator itr = frame.find(planet);
    if (itr != frame.end()) {
        return State(itr->second);
    } else {
        return State(0.0,0.0,0.0,0.0,0.0,0.0,0.0);
    }
}

std::map<Body,State> Frame::getPositions() {
    return frame;
}

bool Frame::engineOn(const Body& planet) {
    std::map<Body, bool>::iterator itr = enginesOn.find(planet);
    if (itr != enginesOn.end()) {
        return itr->second;
    } else {
        return false;
    }
}

std::map<Body,bool> Frame::getAllEngineStatus() {
    return enginesOn;
}

double Frame::getEpoch() const {
    return epoch;
}

bool operator==(const Frame& left, const Frame& right) {
    return (left.epoch == right.epoch) ? true : false;
}
bool operator!=(const Frame& left, const Frame& right) {
    return !(left.epoch == right);
}
bool operator>(const Frame& left, const Frame& right) {
    return (left.epoch > right.epoch) ? true : false;
}
bool operator>=(const Frame& left, const Frame& right) {
    return (left.epoch >= right.epoch) ? true : false;
}
bool operator<(const Frame& left, const Frame& right) {
    return (left.epoch < right.epoch) ? true : false;
}
bool operator<=(const Frame& left, const Frame& right) {
    return (left.epoch <= right.epoch) ? true : false;
}