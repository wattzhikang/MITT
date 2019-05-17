#ifndef MANEUVER_H
#define MANEUVER_H

#define "Body.hpp"

class Maneuver {
    private:
        double startEpoch, endEpoch;
        double thrust;
        Body* body;
    public:
        bool operator==(const Maneuver& right);
        bool operator!=(const Maneuver& right);
        bool operator<(const Maneuver& right);
        bool operator<=(const Maneuver& right);
        bool operator>(const Maneuver& right);
        bool operator>=(const Maneuver& right);
}

#endif