#include "ClosedPoly.h"

CClosedPoly::CClosedPoly(CPoint *(&point), int len, string shape) : CPoly(point, len, move(shape)){
    if(!isClosed())
        throw std::invalid_argument("Poly isn't closed!");
}
bool CClosedPoly::isClosed() const {
    if (dotsArray_[0].getY() == dotsArray_[len_ - 1].getY() && dotsArray_[0].getX() == dotsArray_[len_ - 1].getY())
        return true;
    else
        return false;
}
