#include "../src/Thruster.hpp"
#include "gtest/gtest.h"

/******************************************************************************
 * Thruster is just a struct, so its test will be quite boring
******************************************************************************/

#define ISP_SRB 268.0
#define MS_RAT_SRB 0.05
#define THRST_SRB 14e6

namespace {
    TEST(ThrusterTest, MainTest) {
        Thruster srb(
            ISP_SRB,
            MS_RAT_SRB,
            THRST_SRB
        );

        ASSERT_EQ(srb.getSpecificImpulse(), ISP_SRB);
        ASSERT_EQ(srb.getMassRatio(), MS_RAT_SRB);
        ASSERT_EQ(srb.getMassThrust(), THRST_SRB);
    }
}