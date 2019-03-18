#ifndef PLANET_H
#define PLANET_H

#include <string>

class Planet {
  private:
    std::string name;
    
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
    Planet* center;

    //initial vector elements
    double x_pos, x_vel;
    double y_pos, y_vel;
    double z_pos, z_vel;

  public:
    Planet(std::string c_name,
           double semiMajorAxis,
           double eccentricity,
           double inclination,
           double longAscNode,
           double argPeriapsis,
           double truAnomaly,
           double epoch,
           Planet* centralBody)
      : name(c_name), sma(semiMajorAxis), inc(inclination), lan(longAscNode),
        ape(argPeriapsis), tae(truAnomaly), epch(epoch), center(centralBody)
    {}

    Planet(std::string c_name,
           double x_position,
           double x_velocity,
           double y_position,
           double y_velocity,
           double z_position,
           double z_velocity,
           Planet* centralBody)
      : name(c_name), keplerian(false), center(centralBody), x_pos(x_position),
        x_vel(x_velocity), y_pos(y_velocity), y_vel(y_velocity),
        z_pos(z_position), z_vel(z_velocity)
    {}

    std::string to_string();
};
/*
bool operator==(const Planet& planet1, const Planet& planet2) {
  //TODO
  return true;
}
*/

#endif
