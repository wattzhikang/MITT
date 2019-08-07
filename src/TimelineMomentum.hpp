#ifndef TIMELINE_MOMENTUM_H
#define TIMELINE_MOMENTUM_H

#include "Timeline.hpp"

class TimelineMomentum: public Timeline {
    private:
        State initialState(Body);
    public:
        TimelineMomentum(System system);

        void addEvent(Maneuver);
        void removeEvent(Maneuver);

        System getSystem();
        std::vector<Body> getBodies();
        std::vector<Maneuver> getMission();

        //user will request a frame at a certain time and to a certain precison
        //if frame has already been computed, it will return the frame,
        // if it does not exist, it will be computed, added to the tree,
        //and returned
        Frame getFrame(double epoch, double precision);
};

#endif