#include <iostream>

class Rectangle {
private:
    int a; // Длина первой стороны
    int b; // Длина второй стороны

public:
    // Конструктор
    Rectangle(int lengthA, int lengthB) : a(lengthA), b(lengthB) {}

    // Метод для вывода сторон прямоугольника
    void displaySides() const {
        std::cout << "Стороны прямоугольника: a = " << a << ", b = " << b << std::endl;
    }

    // Метод для вычисления периметра
    int perimeter() const {
        return 2 * (a + b);
    }

    // Метод для вычисления площади
    int area() const {
        return a * b;
    }

    // Свойства для доступа к длинам сторон
    int getA() const { return a; }
    int getB() const { return b; }

    void setA(int lengthA) { a = lengthA; }
    void setB(int lengthB) { b = lengthB; }

    // Свойство для проверки, является ли прямоугольник квадратом
    bool isSquare() const {
        return a == b;
    }

    // Индексатор
    int operator[](int index) const {
        if (index == 0) return a;
        else if (index == 1) return b;
        else {
            std::cerr << "Ошибка: индекс должен быть 0 или 1." << std::endl;
            return -1; // Возвращаем -1 в случае ошибки
        }
    }

    // Перегрузка операций ++ и --
    Rectangle& operator++() { // Увеличение сторон
        ++a;
        ++b;
        return *this;
    }

    Rectangle& operator--() { // Уменьшение сторон
        --a;
        --b;
        return *this;
    }
    Rectangle operator++(int) { // Увеличение сторон (постфиксная)
        Rectangle temp = *this; // Сохраняем текущее состояние
        ++a;
        ++b;
        return temp; // Возвращаем предыдущее состояние
    }

    Rectangle operator--(int) { // Уменьшение сторон (постфиксная)
        Rectangle temp = *this; // Сохраняем текущее состояние
        --a;
        --b;
        return temp; // Возвращаем предыдущее состояние
    }

    // Перегрузка операции * для умножения на скаляр
    Rectangle operator*(int scalar) const {
        return Rectangle(a * scalar, b * scalar);
    }

    // Перегрузка констант true и false для проверки квадрата
    operator bool() const {
        return isSquare();
    }
};

int lab5() {
    setlocale(LC_ALL, "rus");
    Rectangle rect(5, 10); // Создание прямоугольника со сторонами 5 и 10

    rect.displaySides(); // Вывод сторон
    std::cout << "Периметр: " << rect.perimeter() << std::endl; // Вычисление периметра
    std::cout << "Площадь: " << rect.area() << std::endl; // Вычисление площади

    rect.setA(10); // Изменение длины первой стороны
    rect.setB(10); // Изменение длины второй стороны
    std::cout << "После изменения сторон:\n";
    rect.displaySides();

    if (rect) { // Проверка, является ли прямоугольник квадратом
        std::cout << "Прямоугольник является квадратом." << std::endl;
    }
    else {
        std::cout << "Прямоугольник не является квадратом." << std::endl;
    }

    rect++; // Увеличение сторон
    std::cout << "После увеличения:\n";
    rect.displaySides();

    --rect; // Уменьшение сторон
    std::cout << "После уменьшения:\n";
    rect.displaySides();

    Rectangle scaledRect = rect * 2; // Умножение на скаляр
    std::cout << "После умножения на 2:\n";
    scaledRect.displaySides();

    // Использование индексатора
    std::cout << "Сторона a через индексатор: " << rect[0] << std::endl;
    std::cout << "Сторона b через индексатор: " << rect[1] << std::endl;

    return 0;
}
