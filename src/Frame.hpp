/******************************************************************************
Frame.hpp
Author: Zachariah Watt

This represents a snapshot of a gravitational system at an instant in time
******************************************************************************/

#ifndef GRAV_FRAME_H
#define GRAV_FRAME_H

#include <map>

#include "Planet.hpp"
#include "Position.hpp"

class Frame {
    private:
        double epoch;

        //a data structure (map?) of planets <Planet, coordinates>
        std::map<Planet, Position> frame;
    public:
        Frame(double c_epoch) : epoch(c_epoch) {}

        getPosition(Planet& planet) 
};

#endif
