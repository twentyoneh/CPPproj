#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

bool isPunctuation(char ch) {
    return std::ispunct(static_cast<unsigned char>(ch)); // Проверка, является ли символ знаком пунктуации
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
    std::ifstream file("input.txt"); // Открываем файл для чтения
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return 1;
    }

    std::string maxPunctLine; // Строка с максимальным количеством знаков пунктуации
    int maxPunctCount = 0;    // Максимальное количество знаков пунктуации
    std::string currentLine;

    // Читаем файл построчно
    while (std::getline(file, currentLine)) {
        int punctCount = countPunctuationMarks(currentLine); // Считаем знаки пунктуации в строке
        if (punctCount > maxPunctCount) {
            maxPunctCount = punctCount;
            maxPunctLine = currentLine;
        }
    }

    file.close(); // Закрываем файл

    if (!maxPunctLine.empty()) {
        std::cout << "Строка с максимальным количеством знаков пунктуации: " << std::endl;
        std::cout << maxPunctLine << std::endl;
        std::cout << "Количество знаков пунктуации: " << maxPunctCount << std::endl;
    }
    else {
        std::cout << "Файл не содержит строк." << std::endl;
    }

    return 0;
}
