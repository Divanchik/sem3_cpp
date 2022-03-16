#include <cmath>
#include "cpp-rational.h"
namespace cpp
{
    Dot::Dot(): x(0),y(0){}
    Dot::Dot(double a, double b): x(a), y(b){}
    double Dot::_x() const {return x;}// get x
    double Dot::_y() const {return y;}// get y
    void Dot::set(double a, double b)// set x and y
    {
        x = a;
        y = b;
    }


    Line::Line(): A(0), B(0), C(0){}
    Line::Line(double a, double b, double c): A(a), B(b), C(c){}
    void Line::set(const char i, double n)
    {
        switch (i)
        {
            case 'A':
            {
                A = n;
                break;
            }
            case 'B':
            {
                B = n;
                break;
            }
            case 'C':
            {
                C = n;
                break;
            }
        }
    }
    void Line::set(double a, double b, double c)
    {
        A = a;
        B = b;
        C = c;
    }
    double Line::_A() const {return A;}
    double Line::_B() const {return B;}
    double Line::_C() const {return C;}
    double Line::angle_from_x() const// angle between line and x axis
    {
        if (A == 0 && B == 0)
            return NAN;
        double angle = atan(-A/B)*180/3.141;
        if (angle < 0)
            return angle + 180;
        else
            return angle;
    }
    double Line::angle_from_x(Line s)// angle between line and x axis
    {
        if (s._A() == 0 && s._B() == 0)
            return NAN;
        double angle = atan(-s._A()/s._B())*180/3.141;
        if (angle < 0)
            return angle + 180;
        else
            return angle;
    }
    double Line::angle_from(Line s) const// angle between line and another line
    {
        double A1 = A;
        double B1 = B;
        double A2 = s._A();
        double B2 = s._B();
        if (A1 == 0 && B1 == 0 || A2 == 0 && B2 == 0)
            return NAN;
        return (A1*B1+A2*B2)/(sqrt(A1*A1+B1*B1)*sqrt(A2*A2+B2*B2));
    }
    int Line::is_separating_dots(Dot a, Dot b) const//is line separating two dots from each other
    {
        double ya = -(A/B) * a._x() - (C/B);
        double yb = -(A/B) * b._x() - (C/B);
        if ((ya > a._y() && yb < b._y()) || (ya < a._y() && yb > b._y()))
            return 1;
        else
            return 0;
    }
    Dot Line::is_crossing(Line s) const//is line crossing another line
    {
        Dot t;
        if (A/0.001 == s._A()/0.001 && B/0.001 == s._B()/0.001)
        {
            t.set(NAN,NAN);
            return t;
        }
        if (A == 0 && B == 0 || s.angle_from_x() == NAN)
        {
            if (C == s._C())
            {
                t.set(0,C);
                return t;
            }
            else
            {
                t.set(NAN,NAN);
                return t;
            }
        }
        double A1 = s._A();
        double B1 = s._B();
        double C1 = s._C();
        double tx = (C*B1-C1*B)/(A1*B-A*B1);
        double ty = -(A/B)*tx - (C/B);
        t.set(tx,ty);
        return t;
    }
}
