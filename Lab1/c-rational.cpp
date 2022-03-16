#include "c-rational.h"
#include <math.h>
namespace c
{
    double angle_from_x(Line a)// angle between line and x axis
    {
        if (a.A == 0 && a.B == 0)
            return NAN;
        double angle = atan(-a.A/a.B)*180/3.141;
        if (angle < 0)
            return angle + 180;
        else
            return angle;
    }
    double angle_from(const Line a, const Line b)// angle between line and another line
    {
        double A1 = a.A;
        double B1 = a.B;
        double A2 = b.A;
        double B2 = b.B;
        if (A1 == 0 && B1 == 0 || A2 == 0 && B2 == 0)
            return NAN;
        return (A1*B1+A2*B2)/(sqrt(A1*A1+B1*B1)*sqrt(A2*A2+B2*B2));
    }
    int is_separating_dots(const Line l, const Dot a, const Dot b)//is line separating two dots from each other
    {
        double A = l.A;
        double B = l.B;
        double C = l.C;
        double ya = -(A/B) * a.x - (C/B);
        double yb = -(A/B) * b.x - (C/B);
        if (ya > a.y && yb < b.y || ya < a.y && yb > b.y)
            return 1;
        else
            return 0;
    }
    Dot is_crossing(const Line a, const Line b)//is line crossing another line
    {
        double A = a.A;
        double B = a.B;
        double C = a.C;
        double A1 = b.A;
        double B1 = b.B;
        double C1 = b.C;
        Dot t;
        if (A/0.001 == A1/0.001 && B/0.001 == B1/0.001)
        {
            t.x = t.y = NAN;
            return t;
        }
        if (A == 0 && B == 0 || A1 == 0 && B1 == 0)
        {
            if (C == C1)
            {
                t.x = 0;
                t.y = C;
                return t;
            }
            else
            {
                t.x = t.y = NAN;
                return t;
            }
        }
        double tx = (C*B1-C1*B)/(A1*B-A*B1);
        double ty = -(A/B)*tx - (C/B);
        t.x = tx;
        t.y = ty;
        return t;
    }
}
