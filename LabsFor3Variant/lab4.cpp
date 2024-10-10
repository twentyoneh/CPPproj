#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int lab4_1() {
    std::string input;
    int countDots;

    while (true) {
        std::cout << "Введите строку (или 'quit' для выхода): ";
        std::getline(std::cin, input);

        if (input.substr(input.size() - 4) == "quit") {
            std::cout << "Завершение программы.\n";
            break;
        }

        countDots = 0;
        for (char ch : input) {
            if (ch == '.') {
                countDots++;
            }
        }

        std::cout << "Количество точек в строке: " << countDots << std::endl;
    }

    return 0;
}

int lab4_2() {
    std::ifstream inputFile("input.txt");  // Открываем исходный файл для чтения
    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл input.txt" << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;

    // Читаем строки из файла
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();

    if (lines.size() < 2) {
        std::cerr << "Недостаточно строк в файле." << std::endl;
        return 1;
    }

    // Меняем местами четные и нечетные строки
    for (size_t i = 0; i + 1 < lines.size(); i += 2) {
        std::swap(lines[i], lines[i + 1]);
    }

    std::ofstream outputFile("output.txt");  // Открываем новый файл для записи
    if (!outputFile.is_open()) {
        std::cerr << "Не удалось открыть файл output.txt" << std::endl;
        return 1;
    }

    // Записываем измененные строки в новый файл
    for (const auto& ln : lines) {
        outputFile << ln << std::endl;
    }

    outputFile.close();

    std::cout << "Обработка завершена. Результат записан в output.txt" << std::endl;

    return 0;
}

struct TRAIN {
    int NUMR;         // Номер поезда
    std::string TIME; // Время отправления
    std::string NAZN; // Пункт назначения
    std::string OTPR; // Пункт отправления
};

int lab4_3() {
    const int numTrains = 6;
    TRAIN RASP[numTrains];

    // Ввод данных о поездах
    for (int i = 0; i < numTrains; ++i) {
        std::cout << "Введите информацию о поезде #" << i + 1 << ":\n";
        std::cout << "Номер поезда: ";
        std::cin >> RASP[i].NUMR;
        std::cin.ignore(); // Игнорируем символ новой строки после номера

        std::cout << "Время отправления (чч:мм): ";
        std::getline(std::cin, RASP[i].TIME);

        std::cout << "Пункт назначения: ";
        std::getline(std::cin, RASP[i].NAZN);

        std::cout << "Пункт отправления: ";
        std::getline(std::cin, RASP[i].OTPR);
    }

    std::string searchDestination;
    std::cout << "\nВведите пункт назначения для поиска поездов: ";
    std::getline(std::cin, searchDestination);

    bool found = false;
    // Поиск поездов с введенным пунктом назначения
    for (int i = 0; i < numTrains; ++i) {
        if (RASP[i].NAZN == searchDestination) {
            found = true;
            std::cout << "\nНайден поезд:\n";
            std::cout << "Номер поезда: " << RASP[i].NUMR << "\n";
            std::cout << "Время отправления: " << RASP[i].TIME << "\n";
            std::cout << "Пункт отправления: " << RASP[i].OTPR << "\n";
        }
    }

    if (!found) {
        std::cout << "Поездов в пункт назначения '" << searchDestination << "' не найдено.\n";
    }

    return 0;
}