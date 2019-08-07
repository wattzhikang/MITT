/******************************************************************************
 * System.hpp
 * 
 * Author: Zachariah Watt
 * 
 * The purpose of the System class is to (a) hold the configuration of
 * a gravitational system in a static state and (b) to associate Thrusters with Bodies.
******************************************************************************/

#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <unordered_map>
#include <map>

#include "Body.hpp"
#include "Thruster.hpp"

class System {
    private:
        std::vector<Body> bodies;
        std::map<Body, Thruster> thrusters;

        int findBodyIndex(Body);
    public:
        void addBody(Body);
        void removeBody(Body);

        void addThruster(Body, Thruster);
        void removeThruster(Body);
        bool hasThruster(Body);
        Thruster getThruster(Body);

        std::vector<Body> getBodies();
};

#endif