#ifndef ICT_HOMEWORK_1_POLY_H
#define ICT_HOMEWORK_1_POLY_H
#include "Point.h"


class CPoly{

protected:

    CPoint *dotsArray_;
    int len_;
    string shape_;

public:

    explicit CPoly(CPoint* (&point), int len, string shape = "poly"): shape_(move(shape)){
        len_ = len;
        dotsArray_ = new CPoint[len_];

        for(int i = 0; i < len_; i++){
            dotsArray_[i]=point[i];
        }
    }
    CPoly& operator= (const CPoly& p){
        this->dotsArray_ = p.dotsArray_;
        this->len_=p.len_;

        return *this;
    }
    static double vectorModule(const CPoint &a, const CPoint &b) ;

    double getLength() const;

    void printLn ();

    ~CPoly(){
        delete[] dotsArray_;
    }
};
#endif //ICT_HOMEWORK_1_POLY_H
