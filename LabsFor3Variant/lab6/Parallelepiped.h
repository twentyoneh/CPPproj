#ifndef PARALLELEPIPED_H
#define PARALLELEPIPED_H

#include "Quadrilateral.h"

class Parallelepiped : public Quadrilateral {
private:
    double height; // Высота

public:
    Parallelepiped(Point p1, Point p2, Point p3, Point p4, double height); // Конструктор
    double volume() const; // Метод для вычисления объема
    void display() const override; // Переопределение метода отображения
};

#endif // PARALLELEPIPED_H
