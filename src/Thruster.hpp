#ifndef THRUSTER_H
#define THRUSTER_H

class Thruster {
    private:
        double specificImpulse;
        double massRatio; //payload fraction
        double maxThrust;
    public:
        Thruster(
            double specificImpulse,
            double massRatio,
            double maxThrust
            )
            : specificImpulse(specificImpulse),
            massRatio(massRatio),
            maxThrust(maxThrust)
        {}

        double getSpecificImpulse() {return specificImpulse;}
        double getMassRatio() {return massRatio;}
        double getMassThrust() {return maxThrust;}
};

#endif