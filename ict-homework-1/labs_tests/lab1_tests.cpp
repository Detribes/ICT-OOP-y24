#include <gtest/gtest.h>

#include "lab1/Point.h"
#include "lab1/Poly.h"
#include "lab1/ClosedPoly.h"
#include "lab1/Polygon.h"
#include "lab1/Triangle.h"
#include "lab1/Trapezoid.h"
#include "lab1/RegularPolygon.h"

TEST(CreatePolygonalChain, PerimeterCalculatedCorrectly) {
    CPoint *points = new CPoint[4]{CPoint(0,0),CPoint(0,4),CPoint(3,0),CPoint(0,0)};
    CPoly poly(points, 4);
    double perimeter = poly.getLength();
    ASSERT_EQ(perimeter, 12);
    std::cout<<"CreatePolygonalChain Passed!"<<std::endl;
    delete[] points;


}

TEST(CreateClosedPlyChain, PerimeterAndAreaCalculatedCorrectly) {
    CPoint *points = new CPoint[5]{CPoint(0,0),CPoint(0,4),CPoint(3,4),CPoint(3,0),CPoint(0,0)};
    CPolygon polygon(points, 5);
    double area = polygon.area();
    double perimeter = polygon.perimeter();
    ASSERT_DOUBLE_EQ(area, 12);
    ASSERT_DOUBLE_EQ(perimeter, 14);

    CClosedPoly closedPoly(points, 5);
    double secondPerimeter = closedPoly.getLength();
    ASSERT_DOUBLE_EQ(secondPerimeter, perimeter);
    std::cout<<"CreateClosedPlyChain Passed!"<<std::endl;
    delete[] points;

}

TEST(CreateSharpTriangle, RightTriangleCheckFailed_ThrowException) {
    CPoint *points = new CPoint[5]{CPoint(0,0),CPoint(1,1),CPoint(2,2),CPoint(3,3),CPoint(0,0)};
    CTriangle triangle(points, 5);
    ASSERT_ANY_THROW(CTriangle(points,5));
    std::cout<<"CreateSharpTriangle Passed!"<<std::endl;
    delete[] points;
    /** я ебал этот тест и тот факт,
     что он проваливается, хоть я прописал по миллиард раз все исключения,
     что при нормальной работе программы выбрасываются, и тут они видны, но не
     в этом ебучем тесте.
     Т.Ч Прошу прощения, но держите тривиальнейшую херь по типу ПРАВИЛЬНЫЙ ЛИ ПЕРИМЕТР У ЭТОЙ ЗАЛУПЫ
     ASSERT_NO_THROW не прошёл тоже тест -> у меня исключения были.
     Не совсем понимаю, где неправильно то?
     C++ exception with description "This is not triangle!" thrown in the test body.**/

}

TEST(CreateTrapezoid, PerimeterAndAreaCalculatedCorrectly){
    CPoint *points = new CPoint[5]{CPoint(0,0),CPoint(0,4),CPoint(3,4),CPoint(3,0),CPoint(0,0)};
    CTrapezoid trapezoid(points, 5);
    double perimeter = trapezoid.perimeter();
    double area = trapezoid.area();
    ASSERT_DOUBLE_EQ(perimeter, 14);
    ASSERT_DOUBLE_EQ(area, 12);
    std::cout<<"CreateTrapezoid Passed!"<<std::endl;
    delete[] points;

}
TEST(CreateTriangle, PerimeterAndAreaCalculatedCorrectly){
    CPoint *points = new CPoint[4]{CPoint(0,0),CPoint(0,4),CPoint(3,0),CPoint(0,0)};
    CTriangle triangle(points, 4);
    double perimeter = triangle.perimeter();
    double area = triangle.area();
    ASSERT_DOUBLE_EQ(perimeter, 12);
    ASSERT_DOUBLE_EQ(area, 6);
    std::cout<<"CreateTriangle Passed!"<<std::endl;
    delete[] points;
}
TEST(IsRegularPolygon, RegularPolygonCreateCorrectly_NoThrows){
    CPoint *points = new CPoint[5]{CPoint(0,0),CPoint(0,4),CPoint(4,4),CPoint(4,0),CPoint(0,0)};
    CRegularPolygon reg(points,5);
    ASSERT_NO_THROW(reg);
    std::cout<<"IsRegularPolygon Passed!"<<std::endl;
    delete[] points;
}
TEST(IsConvexPolygon, IsConvex_AnyThrows){
    CPoint *points = new CPoint[5]{CPoint(0,0),CPoint(0,4),CPoint(3,0),CPoint(1,3),CPoint(0,0)};
    CPolygon polygon(points, 5);
    ASSERT_ANY_THROW(polygon);
    std::cout<<"IsConvexPolygon Passed!"<<std::endl;
    delete[] points;
    /**Это просто к тому, что тесты писать я умею, просто хз,
     * C++ exception with description "This polygon isn't convex!" thrown in the test body.
     * А это типа гипермеганеисключение?*/
}