#include "TimelineMomentum.hpp"

#include <cmath>

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

TimelineMomentum::~TimelineMomentum() {
    return;
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

std::vector<Maneuver> TimelineMomentum::getTimeline(Body body) {
    std::vector<Maneuver> timeline;
    for (Maneuver maneuver : mission) {
        if (maneuver.getBody() == body) {
            timeline.push_back(maneuver);
        }
    }
    //we don't need to sort it because STL sets store in order per specification
    //TODO: we do need to make sure that the missions don't overlap
    return timeline;
}

State TimelineMomentum::cruiseState(State afterInterval, double timeElapsed, double intervalEnd) {
    double x_pos =
        afterInterval.getXPosition() +
        afterInterval.getXVelocity() * timeElapsed;
    double y_pos =
        afterInterval.getYPosition() +
        afterInterval.getYVelocity() * timeElapsed;
    double z_pos =
        afterInterval.getZPosition() +
        afterInterval.getZVelocity() * timeElapsed;
    return State(
        x_pos, y_pos, z_pos,
        afterInterval.getXVelocity(),
        afterInterval.getYVelocity(),
        afterInterval.getZVelocity(),
        intervalEnd
    );
}

State accelState(State afterInterval, Maneuver maneuver, double timeElapsed, double intervalEnd) {
    double xAccel =
        maneuver.getThrust() *
        sin(maneuver.getProgradeAngle()) *
        cos(maneuver.getNormalAngle());
    double yAccel =
        maneuver.getThrust() *
        sin(maneuver.getProgradeAngle()) *
        sin(maneuver.getNormalAngle());
    double zAccel =
        maneuver.getThrust() *
        cos(maneuver.getNormalAngle());

    double x_pos =
        afterInterval.getXPosition() +
        afterInterval.getXVelocity() * timeElapsed +
        (pow(timeElapsed, 2) * xAccel);
    double y_pos =
        afterInterval.getYPosition() +
        afterInterval.getYVelocity() * timeElapsed +
        (pow(timeElapsed, 2) * yAccel);
    double z_pos =
        afterInterval.getZPosition() +
        afterInterval.getZVelocity() * timeElapsed +
        (pow(timeElapsed, 2) * zAccel);
    return State(
        x_pos, y_pos, z_pos,
        afterInterval.getXVelocity(),
        afterInterval.getYVelocity(),
        afterInterval.getZVelocity(),
        intervalEnd
    );
}

State TimelineMomentum::deriveState(std::vector<Maneuver> timeline, Body body, State initialState, double endEpoch) {
    //invariant #1: afterInterval refers to the state after the last interval
    State afterInterval = initialState;
    //invariant #2: intervalEnd will refer to the ending point of the previous interval
    //intervalStart is not guaranteed to be of any relevance
    double intervalStart, intervalEnd = initialState.getEpoch();
    double timeElapsed;

    //maneuvers don't overlap as per getTimeline's specification
    for (Maneuver maneuver : timeline) {
        //compute cruise phase
        intervalStart = intervalEnd;
        intervalEnd = maneuver.getStart();
        timeElapsed = intervalEnd - intervalStart;
        afterInterval = cruiseState(afterInterval, timeElapsed, intervalEnd);

        //compute accel phase
        intervalStart = intervalEnd;
        intervalEnd = maneuver.getEnd();
        timeElapsed = intervalEnd - intervalStart;
        afterInterval = accelState(afterInterval, maneuver, timeElapsed, intervalEnd);
    }

    //compute final cruise phase
    intervalStart = intervalEnd;
    intervalEnd = endEpoch;
    timeElapsed = intervalEnd - intervalStart;
    afterInterval = cruiseState(afterInterval, timeElapsed, intervalEnd);
}

//this is the business method
Frame TimelineMomentum::computeFrame(double epoch, double precision) {
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

        std::vector<Maneuver> bodyTimeline = getTimeline(prevBody);

        State nextState = deriveState(bodyTimeline, prevBody, prevState, epoch);

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