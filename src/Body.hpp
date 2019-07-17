#ifndef BODY_H
#define BODY_H

#include <string>

#include "State.hpp"

class Body {
  private:
    //intrinsic properties
    std::string name;
    double mass;
    double radius;
    
    //whether to use keplerian elements or vector elements
    bool keplerian;

    //orbital elements
    double sma;
    double ecc;
    double inc;
    double lan;
    double ape;
    double tae;
    double epch;
    Body* center;

    //initial vector elements
    State* stateVectors;

  public:
    Body(std::string c_name,
           double mass,
           double radius,
           double semiMajorAxis,
           double eccentricity,
           double inclination,
           double longAscNode,
           double argPeriapsis,
           double truAnomaly,
           double epoch,
           Body* centralBody)
      : name(c_name), mass(mass), radius(radius), keplerian(true), sma(semiMajorAxis), ecc(eccentricity),
        inc(inclination), lan(longAscNode), ape(argPeriapsis), tae(truAnomaly),
        epch(epoch), center(centralBody)
    {}

    Body(std::string c_name,
           double mass,
           double radius,
           State* state)
      : name(c_name), mass(mass), radius(radius), keplerian(false),
        epch(state->getEpoch()), stateVectors(state)
    {}

    std::string getName() const;
    double getMass() const;
    double getRadius() const;

    bool isKeplerian() const;

    double getSMA() const;
    double getECC() const;
    double getINC() const;
    double getLAN() const;
    double getAPE() const;
    double getTAE() const;
    double getEpoch() const;
    Body* getCenter() const;

    State* getInitialState() const;

    std::string to_string() const;
};

bool operator==(const Body& Body1, const Body& Body2);
bool operator!=(const Body& Body1, const Body& Body2);

bool operator<(const Body& Body1, const Body& Body2);
bool operator<=(const Body& Body1, const Body& Body2);
bool operator>(const Body& Body1, const Body& Body2);
bool operator>=(const Body& Body1, const Body& Body2);

#endif
