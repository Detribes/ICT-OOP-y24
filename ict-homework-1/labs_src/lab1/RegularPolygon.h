#ifndef ICT_HOMEWORK_1_REGULARPOLYGON_H
#define ICT_HOMEWORK_1_REGULARPOLYGON_H
#include "Polygon.h"

class CRegularPolygon : public CPolygon{
public:
    explicit CRegularPolygon(CPoint* (&point), int len, string shape = "regular polygon");

    bool isRegular();

    ~CRegularPolygon()= default;
};
#endif //ICT_HOMEWORK_1_REGULARPOLYGON_H
