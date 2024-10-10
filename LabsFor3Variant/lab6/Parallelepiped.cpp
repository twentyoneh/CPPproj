#include <iostream>
#include "Parallelepiped.h"

Parallelepiped::Parallelepiped(Point p1, Point p2, Point p3, Point p4, double height)
    : Quadrilateral(p1, p2, p3, p4), height(height) {}

double Parallelepiped::volume() const {
    double areaBase = area(); // Площадь основания
    return areaBase * height; // Объем = площадь основания * высота
}

void Parallelepiped::display() const {
    Quadrilateral::display();
    std::cout << "Высота: " << height << std::endl;
    std::cout << "Объем: " << volume() << std::endl;
}
