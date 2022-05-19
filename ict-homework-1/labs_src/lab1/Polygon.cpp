#include "Polygon.h"

CPolygon::CPolygon(CPoint* (&point), int len, string shape) : CClosedPoly(point, len, move(shape)){
    if(!isConvex())
        throw std::invalid_argument("This polygon isn't convex!");
    if(!isClosed())
        throw std::invalid_argument("Part of the plane is not limited by a closed poly");
}
bool CPolygon::isConvex() {

    bool neg = false;
    bool pos = false;
    for(int i = 0; i < len_; i++){
        int a = i;
        int b = (i + 1) % len_;
        int c = (i + 2) % len_;
        double crossProduct = ((dotsArray_[a].getX() - dotsArray_[b].getX()) *
                               (dotsArray_[c].getY() - dotsArray_[b].getY()) -
                               (dotsArray_[a].getY() - dotsArray_[b].getY()) *
                               (dotsArray_[c].getX() - dotsArray_[b].getX()));
        if(crossProduct < 0) neg = true;
        else if(crossProduct > 0) pos = true;
        if(neg && pos) return false;
    }
    return true;

}

double CPolygon::scalarComposition(const CPoint &a, const CPoint &b) {
    return a.getX()*b.getX() + a.getY()*b.getY();
}
CPoint CPolygon::vectorCords(const CPoint &a, const CPoint &b) {
    return CPoint {b.getX() - a.getX(), b.getY() - a.getY()};
}
double CPolygon::perimeter() const {
    return CClosedPoly::getLength();
}
double CPolygon::area() const{
    double sum = 0;

    for (int i = 1; i < len_; i++){
        sum += (dotsArray_[i].getX() + dotsArray_[i - 1].getX()) * (dotsArray_[i - 1].getY() - dotsArray_[i].getY());
    }

    return abs(sum) / 2;
}
void CPolygon::printPolygon() {
    std::cout << "This " << shape_ << " contains " << len_ - 1 << " vertices with these cords: ";

    for (int i = 0; i < len_ - 1; i++)
        std::cout << "(" << dotsArray_[i].getX() << "; " << dotsArray_[i].getY() << ") ";

    std::cout << ".\nPerimeter of your " << shape_ << " is: " << perimeter() << ".";
    std::cout << "\nArea of your " << shape_ << " is: " << area() << ".\n\n";
}