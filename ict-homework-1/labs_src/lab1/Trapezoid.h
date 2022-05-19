#ifndef ICT_HOMEWORK_1_TRAPEZOID_H
#define ICT_HOMEWORK_1_TRAPEZOID_H
#include "Polygon.h"

class CTrapezoid : public CPolygon{
public:
    explicit CTrapezoid(CPoint *(&point), int len, string shape = "trapezoid");
    bool isTrapezoid();

    ~CTrapezoid()=default;
};
#endif //ICT_HOMEWORK_1_TRAPEZOID_H
