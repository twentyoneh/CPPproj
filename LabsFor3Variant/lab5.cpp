#include <iostream>

class Rectangle {
private:
    int a; // ����� ������ �������
    int b; // ����� ������ �������

public:
    // �����������
    Rectangle(int lengthA, int lengthB) : a(lengthA), b(lengthB) {}

    // ����� ��� ������ ������ ��������������
    void displaySides() const {
        std::cout << "������� ��������������: a = " << a << ", b = " << b << std::endl;
    }

    // ����� ��� ���������� ���������
    int perimeter() const {
        return 2 * (a + b);
    }

    // ����� ��� ���������� �������
    int area() const {
        return a * b;
    }

    // �������� ��� ������� � ������ ������
    int getA() const { return a; }
    int getB() const { return b; }

    void setA(int lengthA) { a = lengthA; }
    void setB(int lengthB) { b = lengthB; }

    // �������� ��� ��������, �������� �� ������������� ���������
    bool isSquare() const {
        return a == b;
    }

    // ����������
    int operator[](int index) const {
        if (index == 0) return a;
        else if (index == 1) return b;
        else {
            std::cerr << "������: ������ ������ ���� 0 ��� 1." << std::endl;
            return -1; // ���������� -1 � ������ ������
        }
    }

    // ���������� �������� ++ � --
    Rectangle& operator++() { // ���������� ������
        ++a;
        ++b;
        return *this;
    }

    Rectangle& operator--() { // ���������� ������
        --a;
        --b;
        return *this;
    }
    Rectangle operator++(int) { // ���������� ������ (�����������)
        Rectangle temp = *this; // ��������� ������� ���������
        ++a;
        ++b;
        return temp; // ���������� ���������� ���������
    }

    Rectangle operator--(int) { // ���������� ������ (�����������)
        Rectangle temp = *this; // ��������� ������� ���������
        --a;
        --b;
        return temp; // ���������� ���������� ���������
    }

    // ���������� �������� * ��� ��������� �� ������
    Rectangle operator*(int scalar) const {
        return Rectangle(a * scalar, b * scalar);
    }

    // ���������� �������� true � false ��� �������� ��������
    operator bool() const {
        return isSquare();
    }
};

int lab5() {
    setlocale(LC_ALL, "rus");
    Rectangle rect(5, 10); // �������� �������������� �� ��������� 5 � 10

    rect.displaySides(); // ����� ������
    std::cout << "��������: " << rect.perimeter() << std::endl; // ���������� ���������
    std::cout << "�������: " << rect.area() << std::endl; // ���������� �������

    rect.setA(10); // ��������� ����� ������ �������
    rect.setB(10); // ��������� ����� ������ �������
    std::cout << "����� ��������� ������:\n";
    rect.displaySides();

    if (rect) { // ��������, �������� �� ������������� ���������
        std::cout << "������������� �������� ���������." << std::endl;
    }
    else {
        std::cout << "������������� �� �������� ���������." << std::endl;
    }

    rect++; // ���������� ������
    std::cout << "����� ����������:\n";
    rect.displaySides();

    --rect; // ���������� ������
    std::cout << "����� ����������:\n";
    rect.displaySides();

    Rectangle scaledRect = rect * 2; // ��������� �� ������
    std::cout << "����� ��������� �� 2:\n";
    scaledRect.displaySides();

    // ������������� �����������
    std::cout << "������� a ����� ����������: " << rect[0] << std::endl;
    std::cout << "������� b ����� ����������: " << rect[1] << std::endl;

    return 0;
}
