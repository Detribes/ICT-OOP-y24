#include "Point.h"
#include "Poly.h"
#include "ClosedPoly.h"
#include "Polygon.h"
#include "Triangle.h"
#include "Trapezoid.h"
#include "RegularPolygon.h"
#include <iostream>

int main(){
    CPoint point(1, 3);
    point.print();

    double x, y;
    int len;
    std::cout<<"Enter count of point's: ";
    std::cin>>len;
    CPoint  *points = new CPoint[len];

    for (int i = 0; i < len; i++){
        std::cout<<"Enter coords of #"<<i+1<<" point(x): "<<std::endl;
        std::cin>>x;
        std::cout<<"Enter coords of "<<i+1<<" point(y): "<<std::endl;
        std::cin>>y;
        points[i] = CPoint(x,y);
    }

    CPoly poly(points, len);
    poly.printLn();

    CClosedPoly closedPoly(points, len);
    closedPoly.printLn();

    CPolygon polygon(points, len);
    polygon.printPolygon();

    CTriangle triangle(points, len);
    triangle.printPolygon();

    CTrapezoid trapezoid(points,len);
    trapezoid.printPolygon();

    delete[] points;

    return 0;
}