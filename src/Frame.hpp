/******************************************************************************
Frame.hpp
Author: Zachariah Watt

This represents a snapshot of a gravitational system at an instant in time
******************************************************************************/

#ifndef GRAV_FRAME_H
#define GRAV_FRAME_H

#include <map>

#include "Body.hpp"
#include "Position.hpp"

class Frame {
    private:
        double epoch;

        std::map<Body, State> frame;
    public:
        Frame(double c_epoch) : epoch(c_epoch) {}

        State getPosition(Body& planet);

        bool engineOn(Body);

        double getEpoch();

        bool operator==(const Frame& right);
        bool operator!=(const Frame& right);
        bool operator>(const Frame& right);
        bool operator>=(const Frame& right);
        bool operator<(const Frame& right);
        bool operator<=(const Frame& right);
};

#endif