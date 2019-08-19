/******************************************************************************
Timeline.hpp
Author: Zachariah Watt

This class represents a bound gravitational system throughout time.
******************************************************************************/

#ifndef GRAV_SYSTEM_H
#define GRAV_SYSTEM_H

#include "Frame.hpp"
#include "System.hpp"
#include "Maneuver.hpp"

#include <set>

class Timeline {
    protected:
        System gSystem;
        std::set<Maneuver> mission;
        std::set<Frame> frames;
        
        Frame nearestFrame(double epoch, double precision);
        virtual Frame computeFrame(double epoch, double precision) = 0;
    public:
        Timeline(){};
        ~Timeline(){};
        
        virtual void addEvent(Maneuver) = 0;
        virtual void removeEvent(Maneuver) = 0;

        virtual System getSystem() = 0;
        virtual std::vector<Body> getBodies() = 0;
        virtual std::vector<Maneuver> getMission() = 0;

        //user will request a frame at a certain time and to a certain precison
        //if frame has already been computed, it will return the frame,
        // if it does not exist, it will be computed, added to the tree,
        //and returned
        Frame getFrame(double epoch, double precision);
};
 
#endif
