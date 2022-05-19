#ifndef ICT_HOMEWORK_1_POINT_H
#define ICT_HOMEWORK_1_POINT_H
#pragma once

#include <iostream>
#include <cmath>
#include <utility>
#include <cassert>
#include <string>
#include <stdexcept>

using std::string;
using std::move;

class CPoint{

private:
    double _x, _y;
public:
    explicit CPoint(double x = 0, double y = 0):
            _x(x), _y(y) {};

    CPoint (const CPoint &point) = default;

    CPoint& operator= (const CPoint &point) = default;

    double getX() const { return _x; }
    double getY() const { return _y; }

    void setX(double x) { _x = x; }
    void setY(double y) { _y = y; }

    void print() const;

};
#endif //ICT_HOMEWORK_1_POINT_H
