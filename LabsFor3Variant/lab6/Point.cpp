#include <iostream>
#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) {}

void Point::display() const {
    std::cout << "Точка: (" << x << ", " << y << ")" << std::endl;
}
