#ifndef TIMELINE_MOMENTUM_H
#define TIMELINE_MOMENTUM_H

#include "Timeline.hpp"

class TimelineMomentum: public Timeline {
    private:
        State initialState(Body);

        std::vector<Maneuver> getTimeline(Body);
        State deriveState(std::vector<Maneuver>, Body, State initialState, double endEpoch);
        bool engineOn(std::vector<Maneuver>, Body, State initialState, double endEpoch);
        State cruiseState(State afterInterval, double timeElapsed, double intervalEnd);
    protected:
        Frame computeFrame(double epoch, double precision);
    public:
        TimelineMomentum(System system);
        ~TimelineMomentum();

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