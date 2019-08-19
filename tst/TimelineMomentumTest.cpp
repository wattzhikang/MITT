#include "../src/TimelineMomentum.hpp"
#include "gtest/gtest.h"

namespace {
    TEST(TimelineMomentumTest, PrimaryTest) {
        //define a system of bodies
        State starState;
        Body star("star", 100.0, 10.0, starState);
        State p1State(1.0, 0, 0, 1.0, 0, 0, 0);
        Body p1("planet 1", 1.0, 0.1, p1State);
        State p2State(0.0, 1.0, 0, 0, 1.0, 0, 0);
        Body p2("planet 2", 2, 4, p2State);
        State p3State(0.0, 0, 1.0, 0, 0, 1.0, 0);
        Body p3("planet 1", 3.0, 6, p3State);

        //define a spacecraft
        State shipState(1.0, 0, 0, 0, 0, 0, 0);
        Body ship("vessel", 8e3, 1.0, shipState);
        Thruster shipThruster(300,0.1,1e6);

        //null thruster
        Thruster nullThruster(0,0,0);

        System sol;
        sol.addBody(star);
        sol.addBody(p1);
        sol.addBody(p2);
        sol.addBody(p3);

        sol.addBody(ship);
        sol.addThruster(ship, shipThruster);

        //Now we can test the Timeline
        TimelineMomentum timeline(sol);

        
    }
}