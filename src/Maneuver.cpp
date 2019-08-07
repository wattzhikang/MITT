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

bool operator== (const Maneuver& left, const Maneuver& right) {
    return left.startEpoch == right.startEpoch;
}

bool operator!= (const Maneuver& left, const Maneuver& right) {
    return !(left == right);
}

bool operator< (const Maneuver& left, const Maneuver& right) {
    if (left.startEpoch < right.startEpoch) {
        return true;
    } else {
        return false;
    }
}

bool operator<= (const Maneuver& left, const Maneuver& right) {
    if (left.startEpoch <= right.startEpoch) {
        return true;
    } else {
        return false;
    }
}

bool operator> (const Maneuver& left, const Maneuver& right) {
    if (left.startEpoch > right.startEpoch) {
        return true;
    } else {
        return false;
    }
}

bool operator>= (const Maneuver& left, const Maneuver& right) {
    if (left.startEpoch >= right.startEpoch) {
        return true;
    } else {
        return false;
    }
}