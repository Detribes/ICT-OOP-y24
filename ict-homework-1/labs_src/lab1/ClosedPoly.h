#ifndef ICT_HOMEWORK_1_CLOSEDPOLY_H
#define ICT_HOMEWORK_1_CLOSEDPOLY_H
#include "Poly.h"

class CClosedPoly : public CPoly{

public:
    explicit CClosedPoly(CPoint* (&point), int len, string shape = "closed poly");
    bool isClosed() const;

    ~CClosedPoly()= default;
};
#endif //ICT_HOMEWORK_1_CLOSEDPOLY_H
