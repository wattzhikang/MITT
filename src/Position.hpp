/******************************************************************************
Position.hpp
Author: Zachariah Watt

This class represents a posision in space and time
******************************************************************************/

#ifndef POSITION_H
#define POSITION_H

class Position {
    private:
        double x, y, z;
        double epoch;
    public:
        Position(double c_x, double c_y, double c_z, double c_epoch)
            : x(c_x), y(c_y), z(c_z), epoch(c_epoch)
        {}

        double getX() {return x;}
        double getY() {return y;}
        double getZ() {return z;}

        double getEpoch() {return epoch;}
};

#endif
