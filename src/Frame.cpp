#include "Frame.hpp"

State Frame::getPosition(const Body& planet) {
    std::map<Body, State>::iterator itr = frame.find(planet);
    if (itr != frame.end()) {
        return State(itr->second);
    } else {
        return State(0.0,0.0,0.0,0.0,0.0,0.0,0.0);
    }
}

bool Frame::engineOn(const Body& planet) {
    std::map<Body, bool>::iterator itr = enginesOn.find(planet);
    if (itr != enginesOn.end()) {
        return itr->second;
    } else {
        return false;
    }
}

double Frame::getEpoch() const {
    return epoch;
}

bool Frame::operator==(const Frame& right) {
    return (epoch == right.epoch) ? true : false;
}
bool Frame::operator!=(const Frame& right) {
    return !(*this == right);
}
bool Frame::operator>(const Frame& right) {
    return (epoch > right.epoch) ? true : false;
}
bool Frame::operator>=(const Frame& right) {
    return (epoch >= right.epoch) ? true : false;
}
bool Frame::operator<(const Frame& right) {
    return (epoch < right.epoch) ? true : false;
}
bool Frame::operator<=(const Frame& right) {
    return (epoch <= right.epoch) ? true : false;
}