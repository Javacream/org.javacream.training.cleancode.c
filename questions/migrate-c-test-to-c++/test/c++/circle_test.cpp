#include <gtest/gtest.h>
#include <cmath>
#include <limits>

extern "C" {
#include "circle.h"
}

constexpr double pi = 3.14159265358979323846;
constexpr double tolerance = 1e-10;

TEST(CircleArea, ZeroRadius) { EXPECT_NEAR(area(0.0), 0.0, tolerance); }
TEST(CirclePerimeter, ZeroRadius) { EXPECT_NEAR(perimeter(0.0), 0.0, tolerance); }
TEST(CircleArea, UnitRadius) { EXPECT_NEAR(area(1.0), pi, tolerance); }
TEST(CirclePerimeter, UnitRadius) { EXPECT_NEAR(perimeter(1.0), 2.0 * pi, tolerance); }
TEST(CircleArea, RadiusTwo) { EXPECT_NEAR(area(2.0), 4.0 * pi, tolerance); }
TEST(CirclePerimeter, RadiusTwo) { EXPECT_NEAR(perimeter(2.0), 4.0 * pi, tolerance); }
TEST(CircleArea, FractionalRadius) { EXPECT_NEAR(area(0.5), 0.25 * pi, tolerance); }
TEST(CirclePerimeter, FractionalRadius) { EXPECT_NEAR(perimeter(0.5), pi, tolerance); }
TEST(CircleArea, NegativeRadius) { EXPECT_DOUBLE_EQ(area(-1.0), -1.0); }
TEST(CirclePerimeter, NegativeRadius) { EXPECT_DOUBLE_EQ(perimeter(-1.0), -1.0); }
TEST(CircleArea, NanRadius) { EXPECT_DOUBLE_EQ(area(std::numeric_limits<double>::quiet_NaN()), -1.0); }
TEST(CirclePerimeter, NanRadius) { EXPECT_DOUBLE_EQ(perimeter(std::numeric_limits<double>::quiet_NaN()), -1.0); }
TEST(CircleArea, InfiniteRadius) { EXPECT_DOUBLE_EQ(area(std::numeric_limits<double>::infinity()), -1.0); }
TEST(CirclePerimeter, InfiniteRadius) { EXPECT_DOUBLE_EQ(perimeter(std::numeric_limits<double>::infinity()), -1.0); }
