#ifndef TERMINAL
#define TERMINAL
#include <string>
#include <regex>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <exception>
#include "../src/shape.h"
#include "../src/ellipse.h"
#include "../src/circular_sector.h"
#include "../src/triangle.h"
#include "../src/sort.h"

class UnusefulUserInput : public std::exception
{
public:
    char *what()
    {
        return "Unuseful User Input!";
    }
};

class Terminal
{
public:
    // you can use regular expression to get useful token from "Input string"
    Terminal(const std::string input)
    {
        // Search for Shapes
        _stringForSearch = input;
        std::regex regexSearchAllShapes("(Ellipse|CircularSector)[\\s]{0,}\\([\\s]{0,}[0-9]{1,}.?[0-9]{0,}[\\s]{0,},[\\s]{0,}[0-9]{1,}.?[0-9]{0,}[\\s]{0,}\\)|"
                                        "(Triangle)[\\s]{0,}\\("
                                        "([\\s]{0,}-?[0-9]{1,}.?[0-9]{0,}[\\s]{0,},){5}"
                                        "[\\s]{0,}-?[0-9]{1,}.?[0-9]{0,}[\\s]{0,}\\)");
        std::smatch match;
        while (std::regex_search(_stringForSearch, match, regexSearchAllShapes))
        {
            _shapesStr.push_back(match[0]);
            _stringForSearch = match.suffix().str();
        }
        // Search for Digits
        std::regex searchPositiveNumbers("[0-9]{1,}.?[0-9]{0,}");
        std::regex searchPosAndNegNumbers("-?[0-9]{1,}.?[0-9]{0,}");
        for (int i = 0; i < _shapesStr.size(); ++i)
        {
            if (std::regex_match(_shapesStr[i], std::regex("Ellipse.*")))
            {
                std::sregex_iterator it = std::sregex_iterator(_shapesStr[i].begin(), _shapesStr[i].end(), searchPositiveNumbers);
                std::smatch sm;
                sm = *it;
                double semiMajorAxes = std::stod(sm.str(0));
                it++;
                sm = *it;
                double semiMinorAxes = std::stod(sm.str(0));
                _shapes.push_back(new Ellipse(semiMajorAxes, semiMinorAxes));
            }
            else if (std::regex_match(_shapesStr[i], std::regex("CircularSector.*")))
            {
                std::sregex_iterator it = std::sregex_iterator(_shapesStr[i].begin(), _shapesStr[i].end(), searchPositiveNumbers);
                std::smatch sm;
                sm = *it;
                double radius = std::stod(sm.str(0));
                it++;
                sm = *it;
                double degree = std::stod(sm.str(0));
                _shapes.push_back(new CircularSector(radius, degree));
            }
            else if (std::regex_match(_shapesStr[i], std::regex("Triangle.*")))
            {
                std::vector<double> axis;
                for (std::sregex_iterator it = std::sregex_iterator(_shapesStr[i].begin(), _shapesStr[i].end(), searchPosAndNegNumbers);
                     it != std::sregex_iterator(); it++)
                {
                    std::smatch sm;
                    sm = *it;
                    axis.push_back(std::stod(sm.str(0)));
                }
                _shapes.push_back(new Triangle(axis[0], axis[1], axis[2], axis[3], axis[4], axis[5]));
            }
        }

        _stringForSearch = input;
    }

    std::string showResult()
    {
        if (_stringForSearch == "Unuseful User Input!")
        {
            std::cout << "Unuseful User Input!" << std::endl;
            throw UnusefulUserInput();
        }
        std::smatch match;
        // Search for feature
        std::regex searchFeature(".*(area|perimeter|sumOfSquares).*");
        if (!std::regex_search(_stringForSearch, match, searchFeature))
        {
            std::cout << "Unuseful User Input!" << std::endl;
            throw UnusefulUserInput();
        }
        _feature = match[1];

        // Search for order
        std::regex searchOrder(".*(inc|dec).*");
        if (!std::regex_search(_stringForSearch, match, searchOrder))
        {
            std::cout << "Unuseful User Input!" << std::endl;
            throw UnusefulUserInput();
        }
        _order = match[1];

        // Assign _shapes to _sortShapes
        _sortShapes = new Sort(&_shapes);
        // Contitions to identify which method to use.
        if (_feature == "area" && _order == "inc")
        {
            AscendingComparison ascendingComparison("area");
            _sortShapes->sortArea(ascendingComparison);
        }
        else if (_feature == "area" && _order == "dec")
        {
            DescendingComparison descendingComparison("area");
            _sortShapes->sortArea(descendingComparison);
        }
        else if (_feature == "perimeter" && _order == "inc")
        {
            AscendingComparison ascendingComparison("perimeter");
            _sortShapes->sortArea(ascendingComparison);
        }
        else if (_feature == "perimeter" && _order == "dec")
        {
            DescendingComparison descendingComparison("perimeter");
            _sortShapes->sortArea(descendingComparison);
        }
        else if (_feature == "sumOfSquares" && _order == "inc")
        {
            AscendingComparison ascendingComparison("sumOfSquares");
            _sortShapes->sortArea(ascendingComparison);
        }
        else if (_feature == "sumOfSquares" && _order == "dec")
        {
            DescendingComparison descendingComparison("sumOfSquares");
            _sortShapes->sortArea(descendingComparison);
        }

        std::vector<Shape *>::iterator shapePtr;
        shapePtr = _shapes.begin();
        std::string values = "[";
        std::ostringstream strs;
        if (_feature == "area")
        {
            for (int i = 0; i < _shapes.size(); ++i)
            {
                Shape *temp = *(shapePtr + i);
                if (i != _shapes.size() - 1)
                    values += std::to_string(temp->area()) + ", ";
                else
                    values += std::to_string(temp->area()) + "]";
            }
            return values;
        }
        else if (_feature == "perimeter")
        {
            for (int i = 0; i < _shapes.size(); ++i)
            {
                Shape *temp = *(shapePtr + i);
                if (i != _shapes.size() - 1)
                    values += std::to_string(temp->perimeter()) + ", ";
                else
                    values += std::to_string(temp->perimeter()) + "]";
            }
            return values;
        }
        else if (_feature == "sumOfSquares")
        {
            for (int i = 0; i < _shapes.size(); ++i)
            {
                Shape *temp = *(shapePtr + i);
                if (i != _shapes.size() - 1)
                    values += std::to_string(temp->sumOfSquares()) + ", ";
                else
                    values += std::to_string(temp->sumOfSquares()) + "]";
            }
            return values;
        }
        else
            return "NULL";
    }

private:
    std::vector<std::string> _shapesStr;
    std::vector<Shape *> _shapes;
    Sort *_sortShapes;
    std::string _feature;
    std::string _order;
    std::string _stringForSearch;
};

#endif