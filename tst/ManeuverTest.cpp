#include "../src/Maneuver.hpp"
#include "gtest/gtest.h"

/******************************************************************************
 * This test suite must extensively test the operators
******************************************************************************/

//Layout of Maneuver objects

/*
 *    0 1 2 3 4 5 6 7 8 9
 * M1 *-----*
 * M2     *---*
 * M3     *---------*
 * M4               *---*
 * M5           *-----*
 *    0 1 2 3 4 5 6 7 8 9
 */

//Truth statements

/*
 * M1 < M2, M1 < M3, M1 < M4, M1 < M5
 * M2 == M3, M2 < M4, M2 < M5
 * M3 < M4, M3 < M5
 * M4 > M5
 */

namespace {
    TEST(ManeuverTest, OperatorTests) {
        Maneuver m1(0, 3, 0.5, NULL);
        Maneuver m2(2, 4, 0.5, NULL);
        Maneuver m3(2, 7, 0.5, NULL);
        Maneuver m4(7, 9, 0.2, NULL);
        Maneuver m5(5, 8, 0.1, NULL);

        //implementation of above truth table
        ASSERT_TRUE(m1 < m2);
        ASSERT_TRUE(m1 < m3);
        ASSERT_TRUE(m1 < m4);
        ASSERT_TRUE(m1 < m5);
        ASSERT_TRUE(m2 == m3);
        ASSERT_TRUE(m2 < m4);
        ASSERT_TRUE(m2 < m5);
        ASSERT_TRUE(m3 < m4);
        ASSERT_TRUE(m3 < m5);
        ASSERT_TRUE(m4 > m5);
        
        //extraneous assertions
        ASSERT_TRUE(m3 > m1);
        ASSERT_TRUE(m4 > m1);
        ASSERT_TRUE(m1 != m5);

        //assert falsehoods
        ASSERT_FALSE(m3 > m2);
        ASSERT_FALSE(m1 == m5);
    }
}