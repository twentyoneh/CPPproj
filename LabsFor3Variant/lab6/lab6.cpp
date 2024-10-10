#include <iostream>
#include "Point.h"
#include "Quadrilateral.h"
#include "Parallelepiped.h"

int lab6() {
    setlocale(LC_ALL, "rus");
    // Создаем точки
    Point p1(0, 0);
    Point p2(4, 0);
    Point p3(4, 3);
    Point p4(0, 3);

    // Создаем четырехугольник
    Quadrilateral quad(p1, p2, p3, p4);
    quad.display();
    std::cout << "Площадь четырехугольника: " << quad.area() << std::endl;

    // Создаем параллелепипед
    Parallelepiped para(p1, p2, p3, p4, 5);
    para.display();

    return 0;
}