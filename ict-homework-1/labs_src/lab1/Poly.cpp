#include "Poly.h"

double CPoly::vectorModule(const CPoint &a, const CPoint &b) {
    double x = b.getX() - a.getX();
    double y = b.getY() - a.getY();
    return sqrt(x*x + y*y);
}
double CPoly::getLength() const{
    double length = 0;
    for (int i = 1; i < len_; i++)
        length += vectorModule(dotsArray_[i - 1], dotsArray_[i]);
    return length;
}
void CPoly::printLn (){
    std::cout << "This " << shape_ << " contains " << len_ - 1 << " vertices with these cords: ";
    for (int i = 0; i < len_ - 1; ++i){
        std::cout << "(" << dotsArray_[i].getX() << "; " << dotsArray_[i].getY() << ") ";}
    std::cout << ".\nLength of your " << shape_ << " is: " << getLength() << ".\n\n";
}
