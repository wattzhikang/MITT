#include "../src/System.hpp"
#include "gtest/gtest.h"

namespace {
    TEST(SystemTest, PrimaryTest) {
        //define a system of bodies
        State starState(0,0,0,0,0,0,0);
        Body star("star", 100.0, 10.0, starState);
        State p1State(123.234, 234.54, 234.5, 234.879, 234.0, 3.54, 0);
        Body p1("planet 1", 1.0, 0.1, p1State);
        State p2State(123.234, 34.54, 234.5, 234.879, 234.0, 3.54, 0);
        Body p2("planet 2", 2, 4, p2State);
        State p3State(23.234, 234.54, 234.5, 0.879, 234.0, 3.54, 0);
        Body p3("planet 1", 3.0, 6, p3State);

        //define a spacecraft
        State shipState(32.02, 123.3, 0.33, 1.021, 42, 344, 0);
        Body ship("vessel", 1e-5, 1e-3, 30, 0.5, 1.026, 0.31, 0.45, 3.01, 0, &p3);
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

        ASSERT_TRUE(sol.hasThruster(ship));
        ASSERT_EQ(shipThruster, sol.getThruster(ship));

        ASSERT_FALSE(sol.hasThruster(star));
        ASSERT_EQ(nullThruster, sol.getThruster(p3));
    }
}