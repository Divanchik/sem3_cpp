#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "c-rational.h"
#include "cpp-rational.h"

int strlen(char *s)
{
    int i = 0;
    while (*(s + i))
        i += 1;
    return i;
}
void cut_char(char *s) { s[strlen(s) - 1] = 0; }
int find_char(char c, const char *s)
{
    int i = 0;
    while (*(s + i))
    {
        if (s[i] == c)
            return i;
        i += 1;
    }
    return -1;
}
int count_char(char c, char *s)
{
    int i = 0;
    int n = 0;
    while (*(s + i))
    {
        if (s[i] == c)
            n += 1;
        i += 1;
    }
    return n;
}
int check_sep(char c, char *s)
{
    char num[] = "0123456789";
    int i = count_char(c, s);
    int n = find_char(c, s);
    while (i)
    {
        if (find_char(s[n - 1], num) == -1 || find_char(s[n + 1], num) == -1)
            return 0;
        n += find_char(c, s + n + 1) + 1;
        i -= 1;
    }
    return 1;
}
int check_input(char *s)
{
    if (*s == 0)
        return 0;
    char correct[] = "0123456789.,- ";
    for (int i = 0; i < strlen(s); i++)
        if (find_char(s[i], correct) == -1)
            return 0;
    if (count_char('.', s) > 3 || count_char(',', s) > 3)
        return 0;
    if (count_char('.', s) > 0 && count_char(',', s) > 0)
        return 0;
    if (count_char('.', s) > 0)
        return check_sep('.', s);
    else
        return check_sep(',', s);
}
void cpp::Line::get_data(const char *s)
{
    A = atof(s);
    while (*s == ' ')
        s += 1;
    s += find_char(' ', s) + 1;
    B = atof(s);
    while (*s == ' ')
        s += 1;
    s += find_char(' ', s) + 1;
    C = atof(s);
}
void cpp::Dot::get_data( const char *s)
{
    x = atof(s);
    while (*s == ' ')
        s += 1;
    s += find_char(' ', s) + 1;
    y = atof(s);
}
void c::get_data(Line *l, const char *s)
{
    l->A = atof(s);
    while (*s == ' ')
        s += 1;
    s += find_char(' ', s) + 1;
    l->B = atof(s);
    while (*s == ' ')
        s += 1;
    s += find_char(' ', s) + 1;
    l->C = atof(s);
}
void c::get_data(Dot *d, const char *s)
{
    d->x = atof(s);
    while (*s == ' ')
        s += 1;
    s += find_char(' ', s) + 1;
    d->y = atof(s);
}
void safe_input(char *s, const char *txt)
{
    *s = 0;
    while (check_input(s) == 0)
    {
        printf("%s\n", txt);
        fgets(s, 100, stdin);
        cut_char(s);
    }
}
int main()
{
    //CPP SOLUTION
    printf("CPP SOLUTION\n");
    cpp::Line a, b;
    cpp::Dot d1, d2;
    char buf[100];
    //input
    safe_input(buf, "Input three doubles, separated by space symbols(Line 1):");
    a.get_data(buf);
    safe_input(buf, "Input three doubles, separated by space symbols(Line 2):");
    b.get_data(buf);
    //printing
    printf("Angle between Line 1 and X axis: %.3lf\n", cpp::Line::angle_from_x(a));
    printf("Angle between Line 2 and X axis: %.3lf\n", b.angle_from_x());
    printf("Angle between Line 1 and Line 2: %.3lf\n", a.angle_from(b));
    cpp::Dot cross = a.is_crossing(b);
    printf("Line 1 is crossing Line 2 in dot (%.3lf;%.3lf)\n", cross._x(), cross._y());
    //input
    safe_input(buf, "Input two doubles, separated by space symbols(Dot 1):");
    d1.get_data(buf);
    safe_input(buf, "Input two doubles, separated by space symbols(Dot 2):");
    d2.get_data(buf);
    //printing
    if (a.is_separating_dots(d1, d2))
        printf("Line 1 is separating two given dots\n");
    else
        printf("Line 1 is NOT separating two given dots\n");
    if (b.is_separating_dots(d1, d2))
        printf("Line 2 is separating two given dots\n");
    else
        printf("Line 2 is NOT separating two given dots\n");
    //C SOLUTION
    printf("C SOLUTION\n");
    c::Line c, d;
    c::Dot d3, d4;
    //input
    safe_input(buf, "Input three doubles, separated by space symbols(Line 1):");
    c::get_data(&c, buf);
    safe_input(buf, "Input three doubles, separated by space symbols(Line 2):");
    c::get_data(&d, buf);
    //printing
    printf("Angle between Line 1 and X axis: %.3lf\n", c::angle_from_x(c));
    printf("Angle between Line 2 and X axis: %.3lf\n", c::angle_from_x(d));
    printf("Angle between Line 1 and Line 2: %.3lf\n", c::angle_from(c, d));
    c::Dot cross1 = c::is_crossing(c, d);
    printf("Line 1 is crossing Line 2 in dot (%.3lf;%.3lf)\n", cross1.x, cross1.y);
    //input
    safe_input(buf, "Input two doubles, separated by space symbols(Dot 1):");
    c::get_data(&d3, buf);
    safe_input(buf, "Input two doubles, separated by space symbols(Dot 2):");
    c::get_data(&d4, buf);
    //printing
    if (c::is_separating_dots(c, d3, d4))
        printf("Line 1 is separating two given dots\n");
    else
        printf("Line 1 is NOT separating two given dots\n");
    if (c::is_separating_dots(d, d3, d4))
        printf("Line 2 is separating two given dots\n");
    else
        printf("Line 2 is NOT separating two given dots\n");
    getchar();
    return 0;
}
