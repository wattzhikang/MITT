#ifndef THRUSTER_H
#define THRUSTER_H

class Thruster {
    private:
        double specificImpulse;
        double massRatio;
        double maxThrust;
    public:
        Thruster(
            double specificImpulse,
            double massRatio,
            double maxThrust
            )
            : speficicImpulse(specificImpulse),
            massRatio(massRatio),
            maxThrust(maxThrust)
        {}

        double getSpecificImpulse();
        double getMassRatio();
        double getMassThrust();
}

#endif