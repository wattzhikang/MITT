#include "../src/State.hpp"
#include "gtest/gtest.h"

/******************************************************************************
 * State is just a struct, so its test will be quite boring
******************************************************************************/

namespace {
    TEST(StateTest, MainTest) {
        State state(0, 2, 3,
                    -5, 8, 8,
                    0);

        ASSERT_EQ(state.getXPosition(), 0);
        ASSERT_EQ(state.getYPosition(), 2);
        ASSERT_EQ(state.getZPosition(), 3);
        ASSERT_EQ(state.getXVelocity(), -5);
        ASSERT_EQ(state.getYVelocity(), 8);
        ASSERT_EQ(state.getZVelocity(), 8);
        ASSERT_EQ(state.getEpoch(), 0);
    }
}