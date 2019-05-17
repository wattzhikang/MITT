#ifndef BODY_H
#define BODY_H

#include <string>

#include "State.hpp"

class Body {
  private:
    //intrinsic properties
    std::string name;
    double mass;
    
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
           double semiMajorAxis,
           double eccentricity,
           double inclination,
           double longAscNode,
           double argPeriapsis,
           double truAnomaly,
           double epoch,
           Body* centralBody)
      : name(c_name), sma(semiMajorAxis), inc(inclination), lan(longAscNode),
        ape(argPeriapsis), tae(truAnomaly), epch(epoch), center(centralBody)
    {}

    Body(std::string c_name,
           double x_position,
           double x_velocity,
           double y_position,
           double y_velocity,
           double z_position,
           double z_velocity,
           Body* centralBody)
      : name(c_name), keplerian(false), center(centralBody), x_pos(x_position),
        x_vel(x_velocity), y_pos(y_velocity), y_vel(y_velocity),
        z_pos(z_position), z_vel(z_velocity)
    {}

    std::string to_string();
};
/*
bool operator==(const Body& Body1, const Body& Body2) {
  //TODO
  return true;
}
*/

#endif
