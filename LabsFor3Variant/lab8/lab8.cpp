#include <iostream>
#include <fstream>
#include "FileWriteException.h"

void writeToFile(const std::string& filename, const std::string& data) {
    // Открываем файл только для чтения
    std::ifstream inputFile(filename);
    
    if (!inputFile) {
        std::cerr << "Ошибка: Не удалось открыть файл " << filename << " для чтения." << std::endl;
        return;
    }

    // Попытка записи в файл, который открыт только для чтения
    // Вызываем исключение
    throw FileWriteException("Попытка записи в файл, открытый только для чтения: " + filename);
}

int lab8() {
    try {
        // Путь к файлу
        std::string filename = "example.txt";

        // Попытка записи в файл
        writeToFile(filename, "Новая строка текста");
    }
    catch (const FileWriteException& e) {
        // Обработка исключения
        std::cerr << "Исключение поймано: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        // Общая обработка других исключений
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}
