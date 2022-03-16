#pragma once
namespace c
{
    // Dot structure. Parameters: x, y.
    struct Dot
    {double x,y;};
    // Allows user to input coordinates for Dot.
    void get_data(Dot *d, const char *s);
    // Line structure. Parameters: A, B, C.
    struct Line
    {double A,B,C;};
    // Allows user to input coefficients for Line.
    void get_data(Line *l, const char *s);
    // Returns angle between Line and X axis.
    double angle_from_x(const Line a);
    // Returns angle between Line and Line.
    double angle_from(const Line a, const Line b);
    // Returns True if Line is separating two Dots.
    int is_separating_dots(const Line l, const Dot a, const Dot b);
    // Returns Dot of Line crossing another Line. If Line is NOT crossing another Line, returns Dot(NaN, NaN).
    Dot is_crossing(const Line a, const Line b);
}
