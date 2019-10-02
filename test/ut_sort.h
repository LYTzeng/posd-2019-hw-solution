#ifndef UT_SORT
#define UT_SORT
#include <algorithm>
#include <gtest/gtest.h>
#include <vector>
#include <iterator>
#include <string>
#include <stdio.h>
#include "../src/sort.h"
#include "../src/shape.h"
#include "../src/circular_sector.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"
#include "../src/terminal.h"

class UTSort : public testing::Test
{
protected:
    virtual void SetUp() override
    {
        //                                                             // area()       perimeter() sumOfSquares()
        shapes.push_back(new CircularSector(5, 30));                   // 6.5449847    12.617994   202.05060
        shapes.push_back(new Ellipse(3, 4));                           // 37.699112    22.849556   1943.3253
        shapes.push_back(new Triangle(0.0, -2.0, 0.0, 2.0, 4.0, 0.0)); // 8            12.944272   231.55418
        shapes.push_back(new CircularSector(6, 10));                   // 3.1415927    13.047198   180.09897
        shapes.push_back(new Ellipse(8, 10));                          // 251.32741    58.265482   66560.335
    }

    std::vector<Shape *> shapes;

    virtual void TearDown() override
    {
        std::vector<Shape *>().swap(shapes);
    }

public:
    // Expcted orders
    std::vector<double> areaAscending{3.1415927, 6.5449847, 8, 37.699112, 251.32741};
    std::vector<double> perimeterAscending{12.617994, 12.944272, 13.047198, 22.849556, 58.265482};
    std::vector<double> sumOfSquaresAscending{180.09897, 202.05060, 231.55418, 1943.3253, 66560.335};

    std::vector<double> areaDescending{251.32741, 37.699112, 8, 6.5449847, 3.1415927};
    std::vector<double> perimeterDescending{58.265482, 22.849556, 13.047198, 12.944272, 12.617994};
    std::vector<double> sumOfSquaresDescending{66560.335, 1943.3253, 231.55418, 202.05060, 180.09897};
};

TEST_F(UTSort, SortWithLambda)
{
    // lambda
    auto lambdaAreaAscending = [](Shape *a, Shape *b) { return a->area() < b->area(); };
    auto lambdaPerimeterAscending = [](Shape *a, Shape *b) { return a->perimeter() < b->perimeter(); };
    auto lambdaSumOfSquaresAscending = [](Shape *a, Shape *b) { return a->sumOfSquares() < b->sumOfSquares(); };
    auto lambdaAreaDescending = [](Shape *a, Shape *b) { return a->area() > b->area(); };
    auto lambdaPerimeterDescending = [](Shape *a, Shape *b) { return a->perimeter() > b->perimeter(); };
    auto lambdaSumOfSquaresDescending = [](Shape *a, Shape *b) { return a->sumOfSquares() > b->sumOfSquares(); };
    Sort *sortShapes = new Sort(&shapes);
    // Iterator for vector Shape*
    std::vector<Shape *>::iterator shapePtr;

    sortShapes->sortArea(lambdaAreaAscending);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(areaAscending[i], temp->area(), 0.00001);
    }

    sortShapes->sortPerimeter(lambdaPerimeterAscending);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(perimeterAscending[i], temp->perimeter(), 0.00001);
    }

    sortShapes->sortSumOfSquares(lambdaSumOfSquaresAscending);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(sumOfSquaresAscending[i], temp->sumOfSquares(), 0.01);
    }

    sortShapes->sortArea(lambdaAreaDescending);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(areaDescending[i], temp->area(), 0.00001);
    }

    sortShapes->sortPerimeter(lambdaPerimeterDescending);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(perimeterDescending[i], temp->perimeter(), 0.00001);
    }

    sortShapes->sortSumOfSquares(lambdaSumOfSquaresDescending);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(sumOfSquaresDescending[i], temp->sumOfSquares(), 0.001);
    }
}

TEST_F(UTSort, QuickSortLambda)
{
    // lambda
    auto lambdaAreaAscending = [](Shape *a, Shape *b) { return a->area() < b->area(); };
    auto lambdaPerimeterAscending = [](Shape *a, Shape *b) { return a->perimeter() < b->perimeter(); };
    auto lambdaSumOfSquaresAscending = [](Shape *a, Shape *b) { return a->sumOfSquares() < b->sumOfSquares(); };
    auto lambdaAreaDescending = [](Shape *a, Shape *b) { return a->area() > b->area(); };
    auto lambdaPerimeterDescending = [](Shape *a, Shape *b) { return a->perimeter() > b->perimeter(); };
    auto lambdaSumOfSquaresDescending = [](Shape *a, Shape *b) { return a->sumOfSquares() > b->sumOfSquares(); };
    Sort *sortShapes = new Sort(&shapes);
    // Iterator for vector Shape*
    std::vector<Shape *>::iterator shapePtr;

    sortShapes->quickSort(lambdaAreaAscending);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(areaAscending[i], temp->area(), 0.001);
    }

    sortShapes->quickSort(lambdaPerimeterAscending);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(perimeterAscending[i], temp->perimeter(), 0.001);
    }

    sortShapes->quickSort(lambdaSumOfSquaresAscending);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(sumOfSquaresAscending[i], temp->sumOfSquares(), 0.001);
    }
}

TEST_F(UTSort, SortWithFunc)
{
    // Function
    Sort *sortShapes = new Sort(&shapes);
    std::vector<Shape *>::iterator shapePtr;

    sortShapes->sortArea(areaAscendingComparison);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(areaAscending[i], temp->area(), 0.00001);
    }

    sortShapes->quickSort(areaAscendingComparison);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(areaAscending[i], temp->area(), 0.00001);
    }

    sortShapes->sortArea(areaDescendingComparison);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(areaDescending[i], temp->area(), 0.00001);
    }

    sortShapes->quickSort(areaDescendingComparison);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(areaDescending[i], temp->area(), 0.00001);
    }
}

TEST_F(UTSort, SortWithObjByArea)
{
    // Objects' methods
    Sort *sortShapes = new Sort(&shapes);
    std::vector<Shape *>::iterator shapePtr;

    AscendingComparison ascendingComparison("area");
    sortShapes->sortArea(ascendingComparison);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(areaAscending[i], temp->area(), 0.00001);
    }

    DescendingComparison descendingComparison("area");
    sortShapes->sortArea(descendingComparison);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(areaDescending[i], temp->area(), 0.00001);
    }
}

TEST_F(UTSort, SortWithObjByPerimeter)
{
    // Objects' methods
    Sort *sortShapes = new Sort(&shapes);
    std::vector<Shape *>::iterator shapePtr;

    AscendingComparison ascendingComparison("perimeter");
    sortShapes->sortPerimeter(ascendingComparison);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(perimeterAscending[i], temp->perimeter(), 0.00001);
    }

    DescendingComparison descendingComparison("perimeter");
    sortShapes->sortPerimeter(descendingComparison);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(perimeterDescending[i], temp->perimeter(), 0.00001);
    }
}

TEST_F(UTSort, SortWithObjBysumOfSquares)
{
    // Objects' methods
    Sort *sortShapes = new Sort(&shapes);
    std::vector<Shape *>::iterator shapePtr;

    AscendingComparison ascendingComparison("sumOfSquares");
    sortShapes->sortSumOfSquares(ascendingComparison);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(sumOfSquaresAscending[i], temp->sumOfSquares(), 0.001);
    }

    DescendingComparison descendingComparison("sumOfSquares");
    sortShapes->sortSumOfSquares(descendingComparison);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(sumOfSquaresDescending[i], temp->sumOfSquares(), 0.001);
    }
}

TEST_F(UTSort, SortWithObjByQuickSort)
{
    Sort *sortShapes = new Sort(&shapes);
    std::vector<Shape *>::iterator shapePtr;

    AscendingComparison ascendingArea("area");
    sortShapes->quickSort(ascendingArea);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(areaAscending[i], temp->area(), 0.00001);
    }

    DescendingComparison descendingArea("area");
    sortShapes->sortArea(descendingArea);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(areaDescending[i], temp->area(), 0.00001);
    }

    AscendingComparison ascendingPerimeter("perimeter");
    sortShapes->sortPerimeter(ascendingPerimeter);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(perimeterAscending[i], temp->perimeter(), 0.00001);
    }

    DescendingComparison descendingPerimeter("perimeter");
    sortShapes->sortPerimeter(descendingPerimeter);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(perimeterDescending[i], temp->perimeter(), 0.00001);
    }

    AscendingComparison ascendingSumOfSquares("sumOfSquares");
    sortShapes->sortSumOfSquares(ascendingSumOfSquares);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(sumOfSquaresAscending[i], temp->sumOfSquares(), 0.001);
    }

    DescendingComparison descendingSumOfSquares("sumOfSquares");
    sortShapes->sortSumOfSquares(descendingSumOfSquares);
    shapePtr = shapes.begin();
    for (int i = 0; i < 5; ++i)
    {
        Shape *temp = *(shapePtr + i);
        ASSERT_NEAR(sumOfSquaresDescending[i], temp->sumOfSquares(), 0.001);
    }
}

TEST(TerminalTest, AreaAscending)
{
    Terminal *test = new Terminal("CircularSector(5, 30) Ellipse(3, 4) Triangle(0.0, -2.0, 0.0, 2.0, 4.0, 0.0) "
                                  "CircularSector(6, 10) Ellipse(8, 10) area inc");
    ASSERT_EQ("[3.141593, 6.544985, 8.000000, 37.699112, 251.327412]", test->showResult());
}

TEST(TerminalTest, PerimeterDescending)
{
    Terminal *test = new Terminal("CircularSector(5, 30) Ellipse(3, 4) Triangle(0.0, -2.0, 0.0, 2.0, 4.0, 0.0) "
                                  "CircularSector(6, 10) Ellipse(8, 10) perimeter dec");
    ASSERT_EQ("[58.265482, 22.849556, 13.047198, 12.944272, 12.617994]", test->showResult());
}

TEST(TerminalTest, PerimeterDescendingWithSpecialCharacter)
{
    Terminal *test = new Terminal("CircularSector(5, 30) Ellipse(3, 4) Triangle(0.0, -2.0, 0.0, 2.0, 4.0, 0.0) "
                                  "CircularSector(6, 10) Ellipse$*&%$(8, 10) perimeter^&*^@# dec @^$#*(");
    ASSERT_EQ("[22.849556, 13.047198, 12.944272, 12.617994]", test->showResult());
}

#endif