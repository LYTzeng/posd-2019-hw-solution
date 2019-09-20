#include <gtest/gtest.h>
#include <stdio.h>
#include "../src/shape.h"
#include "../src/circular_sector.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"

TEST(UTShape, CircularSector)
{
    CircularSector cs(5, 30);
    ASSERT_NEAR(6.5449847, cs.area(), 0.0000001);
    ASSERT_NEAR(12.617994, cs.perimeter(), 0.000001);
    ASSERT_NEAR(202.05060, cs.sumOfSquares(), 0.00001);
}

TEST(UTShape, Ellipse)
{
    Ellipse ellipse(3, 4);
    ASSERT_NEAR(37.699112, ellipse.area(), 0.000001);
    ASSERT_NEAR(22.849556, ellipse.perimeter(), 0.000001);
    ASSERT_NEAR(1943.3253, ellipse.sumOfSquares(), 0.0001);
}

TEST(UTShape, Triangle)
{
    Triangle triangle(0.0, -2.0, 0.0, 2.0, 4.0, 0.0);
    ASSERT_EQ(8, triangle.area());
    ASSERT_NEAR(12.944272, triangle.perimeter(), 0.000001);
    ASSERT_NEAR(231.55418, triangle.sumOfSquares(), 0.00001);
}
