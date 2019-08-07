#include "Timeline.hpp"

#include <stdlib.h>

//TODO: a non-member function to translate from perifocal coordinates

Frame Timeline::nearestFrame(double epoch, double precision) {
    Frame nullFrame(epoch);
    std::set<Frame>::iterator lower = frames.lower_bound(nullFrame);
    if (abs(epoch - (*lower).getEpoch()) < precision) {
        return *lower;
    } else if (abs(epoch - (*(lower++)).getEpoch()) < precision) {
        return *lower;
    } else {
        return false;
    }
}

Frame Timeline::getFrame(double epoch, double precision) {
    Frame nearest = nearestFrame(epoch, precision);
    if (abs(epoch - nearest.getEpoch()) < precision) {
        return nearest;
    } else {
        Frame computedFrame = computeFrame(epoch, precision);
        frames.insert(computedFrame);
        return computedFrame;
    }
}