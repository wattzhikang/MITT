#include "../src/Frame.hpp"
#include "gtest/gtest.h"

namespace {
    TEST(FrameTest, PrimaryTest) {
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

        //assemble maps
        std::map<Body, State> frameMap;
        std::map<Body, bool> frameEnginesOn;

        frameMap.insert(std::pair<Body,State>(star, starState));
        frameEnginesOn.insert(std::pair<Body,bool>(star,false));
        frameMap.insert(std::pair<Body,State>(p1, p1State));
        frameEnginesOn.insert(std::pair<Body,bool>(p1,false));
        frameMap.insert(std::pair<Body,State>(p2, p2State));
        frameEnginesOn.insert(std::pair<Body,bool>(p2,false));
        frameMap.insert(std::pair<Body,State>(p3, p3State));
        frameEnginesOn.insert(std::pair<Body,bool>(p3,false));
        frameMap.insert(std::pair<Body,State>(ship, shipState));
        frameEnginesOn.insert(std::pair<Body,bool>(ship,true));

        Frame frame(0, frameMap, frameEnginesOn);

        ASSERT_EQ(0, frame.getEpoch());
        ASSERT_TRUE(starState == frame.getPosition(star));
        ASSERT_TRUE(frame.engineOn(ship));
        ASSERT_FALSE(p3State == frame.getPosition(p2));
        ASSERT_FALSE(frame.engineOn(p2));
    }
}