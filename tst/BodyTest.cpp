#include "../src/Body.hpp"
#include "gtest/gtest.h"

/******************************************************************************
 * Since Body is basically a glorified struct, we shall just test the getters
 * here in the most boring way possible.
******************************************************************************/

namespace {
    TEST(BodyTest, KeplerianTest) {
        Body body(
            "name", //name
            50000,   //mass
            50,     //radius
            500,   //semi-major axis
            0.1,    //eccentricity
            0.559,  //inclination
            0.235,    //longitude of ascending node
            0.718,    //argument of periapsis
            0.433,    //true anomaly at epoch
            3201.23,    //epoch
            NULL    //central body
        );

        ASSERT_STREQ(body.getName().c_str(), "name");
        ASSERT_EQ(body.getMass(), 50000);
        ASSERT_EQ(body.getRadius(), 50);
        ASSERT_TRUE(body.isKeplerian());
        ASSERT_EQ(body.getSMA(), 500);
        ASSERT_EQ(body.getECC(), 0.1);
        ASSERT_EQ(body.getINC(), 0.559);
        ASSERT_EQ(body.getLAN(), 0.235);
        ASSERT_EQ(body.getAPE(), 0.718);
        ASSERT_EQ(body.getTAE(), 0.433);
        ASSERT_EQ(body.getEpoch(), 3201.23);
        ASSERT_TRUE(body.getCenter() == NULL);

        Body body2(
            "name2",
            2342,
            324,
            909234,
            2392,
            23,
            23,
            68,
            123,
            9,
            NULL
        );

        ASSERT_TRUE(body < body2);
        ASSERT_TRUE(body <= body);
        ASSERT_FALSE(body2 < body);
    }

    TEST(BodyTest, VectorTest) {
        State vectors(
            5280.5,
            2134.2,
            1377.89,
            0.586,
            0.013,
            0.099,
            3201.23
        );
        
        Body body(
            "name",
            50000,
            50,
            vectors
        );

        ASSERT_STREQ(body.getName().c_str(), "name");
        ASSERT_EQ(body.getMass(), 50000);
        ASSERT_EQ(body.getRadius(), 50);
        ASSERT_FALSE(body.isKeplerian());
        ASSERT_TRUE(body.getInitialState() == vectors);
    }
}