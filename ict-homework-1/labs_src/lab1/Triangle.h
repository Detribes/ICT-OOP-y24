#ifndef ICT_HOMEWORK_1_TRIANGLE_H
#define ICT_HOMEWORK_1_TRIANGLE_H
#include "Polygon.h"

class CTriangle : public CPolygon {
public:
    explicit CTriangle(CPoint* (&point), int len, string shape = "triangle");
    bool isTriangle();

    ~CTriangle() = default;
};
#endif //ICT_HOMEWORK_1_TRIANGLE_H
