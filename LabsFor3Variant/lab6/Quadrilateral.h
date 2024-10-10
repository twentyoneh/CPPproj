#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include "Point.h"

class Quadrilateral : public Point {
protected:
    Point p1, p2, p3, p4; // Четыре точки вершин

public:
    Quadrilateral(Point p1, Point p2, Point p3, Point p4); // Конструктор
    double area() const; // Метод для вычисления площади
    void display() const override; // Переопределение метода отображения
};

#endif // QUADRILATERAL_H
