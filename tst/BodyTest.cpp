#include "../src/Body.hpp"
#include "gtest/gtest.h"

namespace {
    TEST(BodyTest, Test1) {
        Body body(
            "name",
            5000,
            50,
            5000,
            0.1,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            NULL
        );
    }
}