#include "TimelineMomentum.hpp"

State TimelineMomentum::initialState(Body body) {
    //TODO: need reference for this transformation
}

TimelineMomentum::TimelineMomentum(System system) {
    gSystem = system;

    std::vector<Body> bodies = gSystem.getBodies();

    std::map<Body, State> frameStates;
    std::map<Body, bool> frameEngine;

    for (Body body : bodies) {
        State initialBodyState = body.getInitialState();
        if (body.isKeplerian()) {
            initialBodyState = initialState(body);
        }
        frameStates.insert(std::pair<Body,State>(body, initialBodyState));
        frameEngine.insert(std::pair<Body, bool>(body, false));
    }

    Frame firstFrame(0, frameStates, frameEngine);

    frames.insert(firstFrame);
}

void TimelineMomentum::addEvent(Maneuver maneuver) {
    mission.insert(maneuver);
    //TODO: remove all frames after maneuver
}

void TimelineMomentum::removeEvent(Maneuver maneuver) {
    mission.erase(maneuver);
    //TODO: remove all frams after
}

System TimelineMomentum::getSystem() {
    return gSystem;
}

std::vector<Body> TimelineMomentum::getBodies() {
    return gSystem.getBodies();
}

std::vector<Maneuver> TimelineMomentum::getMission() {
    std::vector<Maneuver> vMission;
    for (Maneuver maneuver : mission) {
        vMission.push_back(maneuver);
    }
    return vMission;
}

//this is the business method
Frame Timeline::computeFrame(double epoch, double precision) {
    //get the previous frame
    Frame previous = *(frames.lower_bound(epoch));

    //compute next positions based on linear motion
    std::map<Body, State> frameStates;
    std::map<Body, bool> frameEngine;

    std::map<Body, State> previousStates = previous.getPositions();
    double timeElapsed = epoch - previous.getEpoch();
    for (std::pair<Body,State> pair : previousStates) {
        Body prevBody = pair.first;
        State prevState = pair.second;
        //compute the next state based on epoch difference
        double x_pos =
            prevState.getXPosition() + prevState.getXVelocity() * timeElapsed;
        double y_pos =
            prevState.getYPosition() + prevState.getYVelocity() * timeElapsed;
        double z_pos =
            prevState.getZPosition() + prevState.getZVelocity() * timeElapsed;
        
        State nextState(
            x_pos, y_pos, z_pos,
            prevState.getXVelocity(),
            prevState.getYVelocity(),
            prevState.getZVelocity(),
            epoch
        );

        frameStates.insert(std::pair<Body,State>(prevBody, nextState));

        //determine whether the engine is on or not
        for (Maneuver maneuver : mission) {
            //determine whether the maneuver is active at this time
            if (maneuver.getStart() < epoch && maneuver.getEnd() > epoch) {
                frameEngine.insert(
                    std::pair<Body,bool>(maneuver.getBody(), true)
                );
            } else {
                frameEngine.insert(
                    std::pair<Body,bool>(maneuver.getBody(), false)
                );
            }
        }
    }

    Frame returnFrame(epoch, frameStates, frameEngine);

    return returnFrame;
}