#pragma once
namespace cpp
{
    // Dot class. Parameters: x, y.
    class Dot
    {
    private:
        double x,y;
    public:
        // Default constructor.
        Dot();
        // Constructor with parameters initialization.
        Dot(double a, double b);
        // Allows user to input coordinates for Dot.
        void get_data(const char *s);
        // Returns x coordinate.
        double _x() const;
        // Returns y coordinate.
        double _y() const;
        // Coordinates initialization.
        void set(double a, double b);
    };
    // Line class. Parameters: A, B, C.
    class Line
    {
    private:
        double A,B,C;
    public:
        // Default constructor.
        Line();
        // Constructor with parameters initialization.
        Line(double a, double b, double c);
        // Allows user to input coefficients for Line.
        void get_data(const char *s);
        // Initialize coefficient with 'i' name.
        void set(const char i, double n);
        // Coefficients initialization.
        void set(double a, double b, double c);
        // Returns A coefficient.
        double _A() const;
        // Returns B coefficient.
        double _B() const;
        // Returns C coefficient.
        double _C() const;
        // Returns angle between Line and X axis.
        double angle_from_x() const;
        // Returns angle between Line and X axis.
        static double angle_from_x(Line s);
        // Returns angle between Line and Line.
        double angle_from(Line s) const;
        // Returns True if Line is separating two Dots.
        int is_separating_dots(Dot a, Dot b) const;
        // Returns Dot of Line crossing another Line. If Line is NOT crossing another Line, returns Dot(NaN, NaN).
        Dot is_crossing(Line s) const;
    };
}
