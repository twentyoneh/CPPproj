#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

bool isPunctuation(char ch) {
    return std::ispunct(static_cast<unsigned char>(ch)); // ��������, �������� �� ������ ������ ����������
}

int countPunctuationMarks(const std::string& line) {
    int count = 0;
    for (char ch : line) {
        if (isPunctuation(ch)) {
            count++;
        }
    }
    return count;
}

int lab9_1() {
    std::ifstream file("input.txt"); // ��������� ���� ��� ������
    if (!file.is_open()) {
        std::cerr << "�� ������� ������� ����!" << std::endl;
        return 1;
    }

    std::string maxPunctLine; // ������ � ������������ ����������� ������ ����������
    int maxPunctCount = 0;    // ������������ ���������� ������ ����������
    std::string currentLine;

    // ������ ���� ���������
    while (std::getline(file, currentLine)) {
        int punctCount = countPunctuationMarks(currentLine); // ������� ����� ���������� � ������
        if (punctCount > maxPunctCount) {
            maxPunctCount = punctCount;
            maxPunctLine = currentLine;
        }
    }

    file.close(); // ��������� ����

    if (!maxPunctLine.empty()) {
        std::cout << "������ � ������������ ����������� ������ ����������: " << std::endl;
        std::cout << maxPunctLine << std::endl;
        std::cout << "���������� ������ ����������: " << maxPunctCount << std::endl;
    }
    else {
        std::cout << "���� �� �������� �����." << std::endl;
    }

    return 0;
}
