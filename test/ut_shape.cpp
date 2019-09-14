#include <gtest/gtest.h>
#include "../src/circular_sector.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"

int main(int argc,char ** argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

TEST (UTShape, CircularSector)
{
    CircularSector cs(5, 30);
    ASSERT_NEAR(6.5449847, cs.area(), 0.0000001);
    ASSERT_NEAR(12.617994, cs.perimeter(), 0.000001);

}

TEST (UTShape, Ellipse)
{
    Ellipse ellipse(3, 4);
    ASSERT_NEAR(37.699112, ellipse.area(), 0.000001);
    ASSERT_NEAR(22.849556, ellipse.perimeter(), 0.000001);
}

TEST (UTShape, Triangle)
{
    double point1[2] = {0.0, -2.0},
            point2[2] = {0.0, 2.0},
            point3[2] = {4.0, 0.0};

    Triangle triangle( point1, point2, point3);
    ASSERT_EQ(8, triangle.area());
    ASSERT_NEAR(12.944272, triangle.perimeter(), 0.000001);
}
