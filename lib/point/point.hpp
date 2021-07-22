#ifndef POINT_H
#define POINT_H
#include <iostream>

using namespace std;

namespace gmt{
class Point{
    double x, y;
public:
    Point(double _x, double _y): x(_x), y(_y) {};
    void set_cors(double _x, double _y);
    double get_x(void);
    double get_y(void);

    friend std::ostream& operator<<(std::ostream &os, const Point &p);
    friend double distance(const Point &p1, const Point &p2);

};
}

#endif