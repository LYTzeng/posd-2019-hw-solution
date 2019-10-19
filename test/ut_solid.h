#ifndef UT_SOLID
#define UT_SOLID

#include <gtest/gtest.h>
#include <vector>
#include <iterator>
#include <iostream>
#include "../src/solid.h"
#include "../src/cone.h"
#include "../src/square_cylinder.h"
#include "../src/triangular_pyramid.h"
#include "../src/complex_solids.h"

TEST(CONE, TestCone)
{
    Solid *cone = new Cone(0, 0, 1, 1, 5);
    ASSERT_NEAR(6.2831853, cone->bottomArea(), 0.00001);
    ASSERT_NEAR(10.4719756, cone->volume(), 0.00001);
}

TEST(CONE, TestException)
{
    try
    {
        Solid *cone = new Cone(0, 0, 0, 0, 5);
    }
    catch (std::string e)
    {
        ASSERT_EQ("Bottom is not a Circle!", e);
    }
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

TEST(TRIANGULAR, TestException)
{
    try
    {
        Solid *triangularPyramid = new TriangularPyramid(0, 0, 0, 1, 0, 2, 5);
    }
    catch (std::string e)
    {
        ASSERT_EQ("Bottom is not a Triangle!", e);
    }
}

TEST(COMPLEX, TestAdd_BottomArea_Volume)
{
    std::vector<Solid *> solids;
    solids.push_back(new Cone(0, 0, 1, 1, 5));
    ComplexSolids *complexSolids = new ComplexSolids(&solids);
    Solid *squareCylinder = new SquareCylinder(2, 3);
    complexSolids->add(squareCylinder);
    ASSERT_NEAR(10.2831853, complexSolids->bottomArea(), 0.00001);
    ASSERT_NEAR(22.4719756, complexSolids->volume(), 0.00001);
    ASSERT_EQ(2, complexSolids->numberOfChild());
}

TEST(CONPLEX, FIND)
{
    std::vector<Solid *> solids;
    ComplexSolids *complexSolids = new ComplexSolids(&solids);
    complexSolids->add(new SquareCylinder(2, 3));                   // vol=12 bot=4
    complexSolids->add(new Cone(0, 0, 1, 1, 5));                    // vol=10.4719756 bot=6.2831853
    complexSolids->add(new TriangularPyramid(0, 0, 0, 4, 3, 0, 5)); // vol=10 bot=6
    std::vector<Solid *> findResult = complexSolids->find(9, 10, 5, 6.1111);
    ASSERT_NEAR(6, findResult[0]->bottomArea(), 0.0001);
    ASSERT_NEAR(10, findResult[0]->volume(), 0.0001);
}

#endif