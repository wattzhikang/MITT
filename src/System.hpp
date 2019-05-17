#ifndef SYSTEM_H
#define SYSTEM_H

#include "Body.hpp"
#include "Thruster.hpp"

class System {
    private:
        std::vector<Body> bodies;
        std::unordered_map<Body*, Thruster> thrusters;
    public:
        void addBody(Body);
        void removeBody(Body);

        void addThruster(Body, Thruster);
        void removeThruster(Body);

        std::vector<Body> getBodies();
}

#endif