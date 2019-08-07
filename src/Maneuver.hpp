#ifndef MANEUVER_H
#define MANEUVER_H

#include "Body.hpp"

class Maneuver {
    private:
        double startEpoch, endEpoch;
        double thrust;
        Body body;

        bool overlapEarlierLatter(const Maneuver& earlier,
                                  const Maneuver& latter);
    public:
        Maneuver(
            double startEpoch,
            double endEpoch,
            double thrust,
            Body body
        ): startEpoch(startEpoch),
            endEpoch(endEpoch),
            thrust(thrust),
            body(body)
        {}

        double getStart() {return startEpoch;}
        double getEnd() {return endEpoch;}
        double getThrust() {return thrust;}
        Body getBody() {return body;}

        /*
         * Note: all the following methods only compare
         * the Maneuver's chronological order.
        */

        bool overlaps (const Maneuver& right);

        friend bool operator==(const Maneuver& left, const Maneuver& right);
        friend bool operator!=(const Maneuver& left, const Maneuver& right);
        friend bool operator<(const Maneuver& left, const Maneuver& right);
        friend bool operator<=(const Maneuver& left, const Maneuver& right);
        friend bool operator>(const Maneuver& left, const Maneuver& right);
        friend bool operator>=(const Maneuver& left, const Maneuver& right);
};

#endif