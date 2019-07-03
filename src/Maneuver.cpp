#include "Maneuver.hpp"

bool Maneuver::overlapEarlierLatter(
    const Maneuver& earlier, const Maneuver& latter) {
        if ((earlier.startEpoch < latter.startEpoch &&
             latter.startEpoch > earlier.endEpoch) ||
            (earlier.startEpoch < latter.endEpoch &&
             latter.endEpoch > earlier.endEpoch))
            {
                return true;
        } else {
            return false;
        }
}

bool Maneuver::overlaps(const Maneuver& right) {
    if (startEpoch < right.startEpoch) {
        return overlapEarlierLatter(*this, right);
    } else {
        return overlapEarlierLatter(right, *this);
    }
}

bool Maneuver::operator== (const Maneuver& right) {
    return startEpoch == right.startEpoch;
}

bool Maneuver::operator!= (const Maneuver& right) {
    return !(*this==right);
}

bool Maneuver::operator< (const Maneuver& right) {
    if (startEpoch < right.startEpoch) {
        return true;
    } else {
        return false;
    }
}

bool Maneuver::operator<= (const Maneuver& right) {
    if (startEpoch <= right.startEpoch) {
        return true;
    } else {
        return false;
    }
}

bool Maneuver::operator> (const Maneuver& right) {
    if (startEpoch > right.startEpoch) {
        return true;
    } else {
        return false;
    }
}

bool Maneuver::operator>= (const Maneuver& right) {
    if (startEpoch >= right.startEpoch) {
        return true;
    } else {
        return false;
    }
}