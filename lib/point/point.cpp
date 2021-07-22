#include "point.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace gmt;


double gmt::Point::get_x(){
    return x;
}

double gmt::Point::get_y(){
    return y;
}

void gmt::Point::set_cors(double _x, double _y){
    x = _x;
    y = _y;
}

ostream& gmt::operator<<(ostream &os, const gmt::Point &p){
    os << "x:" << p.x << " y:" << p.y;
    return os;
}

double gmt::distance(const gmt::Point &p1, const gmt::Point &p2){
    return static_cast<double>(sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2)));
} 





