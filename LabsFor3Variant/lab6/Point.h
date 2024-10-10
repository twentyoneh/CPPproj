#ifndef POINT_H
#define POINT_H

class Point {
protected:
    double x; // Координата X
    double y; // Координата Y

public:
    Point(double x = 0.0, double y = 0.0); // Конструктор
    virtual void display() const; // Метод для отображения координат
};

#endif // POINT_H
