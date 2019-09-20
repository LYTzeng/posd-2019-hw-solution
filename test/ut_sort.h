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

class UTSort : public testing::Test
{
protected:
    virtual void SetUp() override
    {
        // area()       perimeter() sumOfSquares()
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
    std::vector<double>areaAscending = {3.1415927, 6.5449847, 8, 37.699112, 251.32741};
    std::vector<double>perimeterAscending = {12.617994, 12.944272, 13.047198, 22.849556, 58.265482};
    std::vector<double>sumOfSquaresAscending = {180.09897, 202.05060, 231.55418, 1943.3253, 66560.335};
    //TODO: quickSort()
    // std::vector<double>quickSortAscending = {};

    std::vector<double>areaDescending = {251.32741, 37.699112, 8, 6.5449847, 3.1415927};
    std::vector<double>perimeterDescending = {58.265482, 22.849556, 13.047198, 12.944272, 12.617994};
    std::vector<double>sumOfSquaresDescending = {66560.335, 1943.3253, 231.55418, 202.05060, 180.09897};
    //TODO: quickSort()
    // std::vector<double>quickSortDescending = {};
};

TEST_F(UTSort, SortWithLambda)
{
    // lambda
    auto lambdaAreaAscending = [](Shape *a, Shape *b) { return a->area() < b->area(); };
    auto lambdaPerimeterAscending = [](Shape *a, Shape *b) { return a->perimeter() < b->perimeter(); };
    auto lambdaSumOfSquaresAscending = [](Shape *a, Shape *b) { return a->sumOfSquares() < b->sumOfSquares(); };
    auto lambdaQuickSortAscending = [](Shape *a, Shape *b) { return a->area() < b->area(); };
    auto lambdaAreaDescending = [](Shape *a, Shape *b) { return a->area() > b->area(); };
    auto lambdaPerimeterDescending = [](Shape *a, Shape *b) { return a->perimeter() > b->perimeter(); };
    auto lambdaSumOfSquaresDescending = [](Shape *a, Shape *b) { return a->sumOfSquares() > b->sumOfSquares(); };
    auto lambdaQuickSortDescending = [](Shape *a, Shape *b) { return a->area() > b->area(); };
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
    printf("%f\n%f\n%f\n", shapePtr[0]->perimeter(), shapePtr[1]->perimeter(), shapePtr[2]->perimeter());
    printf("%f\n%f\n", shapePtr[3]->perimeter(), shapePtr[4]->perimeter());
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

    // //TODO: Test case
    sortShapes->quickSort(lambdaQuickSortAscending);

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

    //TODO:
    sortShapes->quickSort(lambdaQuickSortDescending);
}

TEST_F(UTSort, SortWithFunc)
{
    // Function
    Sort *sortShapes = new Sort(&shapes);
    sortShapes->sortArea(areaAscendingComparison);
    sortShapes->quickSort(areaAscendingComparison);
    sortShapes->sortArea(areaDescendingComparison);
    sortShapes->quickSort(areaDescendingComparison);
}

TEST_F(UTSort, ShapesSortByArea)
{
    // Objects' methods
    Sort *sortShapes = new Sort(&shapes);
    AscendingComparison ascendingComparison("area");
    sortShapes->sortArea(ascendingComparison);
    AscendingComparison descendingComparison("area");
    sortShapes->sortArea(descendingComparison);
}
TEST_F(UTSort, ShapesSortByperimeter)
{
    // Objects' methods
    Sort *sortShapes = new Sort(&shapes);
    AscendingComparison ascendingComparison("perimeter");
    sortShapes->sortPerimeter(ascendingComparison);
    AscendingComparison descendingComparison("perimeter");
    sortShapes->sortPerimeter(descendingComparison);
}
TEST_F(UTSort, ShapesSortBysumOfSquares)
{
    // Objects' methods
    Sort *sortShapes = new Sort(&shapes);
    AscendingComparison ascendingComparison("sumOfSquares");
    sortShapes->sortSumOfSquares(ascendingComparison);
    AscendingComparison descendingComparison("sumOfSquares");
    sortShapes->sortSumOfSquares(descendingComparison);
}
