#include "Trapezoid.h"

CTrapezoid::CTrapezoid(CPoint *(&point), int len, string shape) : CPolygon(point, len, move(shape)) {
    if(!isTrapezoid())
        throw std::invalid_argument("This is not a Trapezoid!");
}
bool CTrapezoid::isTrapezoid() {

    double coeff1 = abs((dotsArray_[1].getY() - dotsArray_[0].getY()) / (dotsArray_[1].getX() - dotsArray_[0].getX() + INT16_MAX));
    double coeff2 = abs((dotsArray_[2].getY() - dotsArray_[1].getY()) / (dotsArray_[2].getX() - dotsArray_[1].getX() + INT16_MAX));
    double coeff3 = abs((dotsArray_[3].getY() - dotsArray_[2].getY()) / (dotsArray_[3].getX() - dotsArray_[2].getX() + INT16_MAX));
    double coeff4 = abs((dotsArray_[3].getY() - dotsArray_[0].getY()) / (dotsArray_[3].getX() - dotsArray_[0].getX() + INT16_MAX));

    if (((coeff1 == coeff3) || (coeff2 == coeff4)) && ((len_ - 1) == 4)){
        return true;}

    return false;
}