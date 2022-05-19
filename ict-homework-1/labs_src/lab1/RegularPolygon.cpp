#include "RegularPolygon.h"

CRegularPolygon::CRegularPolygon(CPoint *(&point), int len, string shape) : CPolygon(point, len, move(shape)) {
    if(!isRegular())
        throw std::invalid_argument("This is not regular polygon!");
}
bool CRegularPolygon::isRegular() {
    double temp;
    double first_line = vectorModule(dotsArray_[0], dotsArray_[1]);
    for (int i = 2; i < len_; i++){
        temp = vectorModule(dotsArray_[i - 1], dotsArray_[i]);
        if (temp != first_line) {
            return false;
        }
    }
    return true;
}