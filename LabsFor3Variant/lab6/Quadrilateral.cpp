#include <iostream>
#include "Quadrilateral.h"

Quadrilateral::Quadrilateral(Point p1, Point p2, Point p3, Point p4)
    : Point(), p1(p1), p2(p2), p3(p3), p4(p4) {}

double Quadrilateral::area() const {
    // Примерная формула площади (требует уточнения для произвольного четырехугольника)
    return 0.0; // Реализуйте формулу площади
}

void Quadrilateral::display() const {
    std::cout << "Четырехугольник с вершинами:\n";
    p1.display();
    p2.display();
    p3.display();
    p4.display();
}
