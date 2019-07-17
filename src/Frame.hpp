/******************************************************************************
Frame.hpp
Author: Zachariah Watt

This represents a snapshot of a gravitational system at an instant in time
******************************************************************************/

#ifndef GRAV_FRAME_H
#define GRAV_FRAME_H

#include <map>

#include "Body.hpp"
#include "State.hpp"

class Frame {
    private:
        double epoch;

        std::map<Body, State> frame;
        std::map<Body, bool> enginesOn;
    public:
        Frame(double c_epoch, std::map<Body, State> frame,
            std::map<Body, bool> enginesOn)
        : epoch(c_epoch),
            frame(frame),
            enginesOn(enginesOn)
        {}

        State getPosition(const Body& planet);

        bool engineOn(const Body& planet);

        double getEpoch() const;

        bool operator==(const Frame& right);
        bool operator!=(const Frame& right);
        bool operator>(const Frame& right);
        bool operator>=(const Frame& right);
        bool operator<(const Frame& right);
        bool operator<=(const Frame& right);
};

#endif