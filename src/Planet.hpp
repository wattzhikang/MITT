#ifndef PLANET_H
#define PLANET_H

#include <string>

class Planet {
  private:
    std::string name;
    int sma;
    float ecc;
    float inc;
    float lan;
    float ape;
    float tae;
    double epch;

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

    std::string to_string();
};

#endif
