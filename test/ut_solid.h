#ifndef UT_SOLID
#define UT_SOLID

#include <gtest/gtest.h>
#include <vector>
#include <iterator>
#include <iostream>
#include "../src/solid.h"
#include "../src/cone.h"
#include "../src/complex_solids.h"
#include "../src/square_cylinder.h"
#include "../src/triangular_pyramid.h"

TEST(CONE, TestCone)
{
    Solid *cone = new Cone(0, 0, 1, 1, 5);
    ASSERT_NEAR(6.2831853, cone->bottomArea(), 0.00001);
    ASSERT_NEAR(10.4719756, cone->volume(), 0.00001);
}

TEST(SQUARE_CYLINDER, TestSquareCylinder)
{
    Solid *squareCylinder = new SquareCylinder(2, 3);
    ASSERT_NEAR(4, squareCylinder->bottomArea(), 0.00001);
    ASSERT_NEAR(12, squareCylinder->volume(), 0.00001);
}

TEST(TRIANGULAR, TestTriangularPyramid)
{
    Solid *triangularPyramid = new TriangularPyramid(0, 0, 0, 4, 3, 0, 5);
    ASSERT_NEAR(6, triangularPyramid->bottomArea(), 0.0000001);
    ASSERT_NEAR(10, triangularPyramid->volume(), 0.0000001);
}

#endif