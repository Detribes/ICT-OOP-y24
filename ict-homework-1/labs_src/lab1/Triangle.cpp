#include "Triangle.h"

CTriangle::CTriangle(CPoint *(&point), int len, string shape) : CPolygon(point, len, move(shape)) {
    if(!isTriangle())
        throw std::invalid_argument("This is not triangle!");
}
bool CTriangle::isTriangle() {

    if (len_-1 != 3){
       return false;
    }
    double a = vectorModule(dotsArray_[0], dotsArray_[1]);
    double b = vectorModule(dotsArray_[1], dotsArray_[2]);
    double c = vectorModule(dotsArray_[2], dotsArray_[0]);
    if (a + b > c && a + c > b && b + c > a){
        return true;
    }
    else{
       return false;
    }
}