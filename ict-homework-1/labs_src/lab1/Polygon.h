#ifndef ICT_HOMEWORK_1_POLYGON_H
#define ICT_HOMEWORK_1_POLYGON_H
#include "ClosedPoly.h"

class CPolygon : protected CClosedPoly{

public:
    explicit CPolygon(CPoint* (&point), int len, string shape = "polygon");

    CPolygon& operator= (const CPolygon& p){
        this->dotsArray_ = p.dotsArray_;

        return *this;
    }
    bool isConvex();

    double perimeter() const;

    double area() const;

    double scalarComposition(const CPoint &a, const CPoint &b);

    CPoint vectorCords(const CPoint &a, const CPoint &b);

    void printPolygon();

    ~CPolygon()= default;
};
#endif //ICT_HOMEWORK_1_POLYGON_H
