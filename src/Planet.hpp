#ifndef PLANET_H
#define PLANET_H

#include <string>

class Planet {
  private:
    std::string name;
    
    //whether to use keplerian elements or vector elements
    bool keplerian;

    //orbital elements
    int sma;
    float ecc;
    float inc;
    float lan;
    float ape;
    float tae;
    double epch;
    Planet& centralBody;

    //vector elements
    double x_pos, x_vel;
    double y_pos, y_vel;
    double z_pos, z_vel;

  public:
    Planet(std::string c_name,
           int semiMajorAxis,
           float eccentricity,
           float inclination,
           float longAscNode,
           float argPeriapsis,
           float truAnomaly,
           double epoch)
      : name(c_name), sma(semiMajorAxis), inc(inclination), lan(longAscNode),
        ape(argPeriapsis), tae(truAnomaly), epch(epoch)
    {}

    Planet(std::string name c_name,
           double x_position,
           double x_velocity,
           double y_position,
           double y_velocity,
           double z_position,
           double z_velocity)
      : name(c_name), x_pos(x_position), x_vel(x_velocity), y_pos(y_velocity),
        y_vel(y_velocity), z_pos(z_position), keplerian(false)
      {}

    std::string to_string();
};

bool operator==(const Planet& planet1, const Planet& planet2) {
  //TODO
}

#endif
