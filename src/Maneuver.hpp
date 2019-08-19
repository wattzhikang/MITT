#ifndef MANEUVER_H
#define MANEUVER_H

#include "Body.hpp"

class Maneuver {
    private:
        double startEpoch, endEpoch;

        double progradeRetrograde, normalAntinormal; //these are angles in radians

        double thrust;

        Body body;

        bool overlapEarlierLatter(const Maneuver& earlier,
                                  const Maneuver& latter);
    public:
        Maneuver(
            double startEpoch,
            double endEpoch,
            double progradeRetrograde,
            double normalAntinormal,
            double thrust,
            Body body
        ): startEpoch(startEpoch),
            endEpoch(endEpoch),
            progradeRetrograde(progradeRetrograde),
            normalAntinormal(normalAntinormal),
            thrust(thrust),
            body(body)
        {}

        double getStart() {return startEpoch;}
        double getEnd() {return endEpoch;}
        double getThrust() {return thrust;}
        double getProgradeAngle() {return progradeRetrograde;}
        double getNormalAngle() {return normalAntinormal;}
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