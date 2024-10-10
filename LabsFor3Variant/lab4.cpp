#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int lab4_1() {
    std::string input;
    int countDots;

    while (true) {
        std::cout << "������� ������ (��� 'quit' ��� ������): ";
        std::getline(std::cin, input);

        if (input.substr(input.size() - 4) == "quit") {
            std::cout << "���������� ���������.\n";
            break;
        }

        countDots = 0;
        for (char ch : input) {
            if (ch == '.') {
                countDots++;
            }
        }

        std::cout << "���������� ����� � ������: " << countDots << std::endl;
    }

    return 0;
}

int lab4_2() {
    std::ifstream inputFile("input.txt");  // ��������� �������� ���� ��� ������
    if (!inputFile.is_open()) {
        std::cerr << "�� ������� ������� ���� input.txt" << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;

    // ������ ������ �� �����
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();

    if (lines.size() < 2) {
        std::cerr << "������������ ����� � �����." << std::endl;
        return 1;
    }

    // ������ ������� ������ � �������� ������
    for (size_t i = 0; i + 1 < lines.size(); i += 2) {
        std::swap(lines[i], lines[i + 1]);
    }

    std::ofstream outputFile("output.txt");  // ��������� ����� ���� ��� ������
    if (!outputFile.is_open()) {
        std::cerr << "�� ������� ������� ���� output.txt" << std::endl;
        return 1;
    }

    // ���������� ���������� ������ � ����� ����
    for (const auto& ln : lines) {
        outputFile << ln << std::endl;
    }

    outputFile.close();

    std::cout << "��������� ���������. ��������� ������� � output.txt" << std::endl;

    return 0;
}

struct TRAIN {
    int NUMR;         // ����� ������
    std::string TIME; // ����� �����������
    std::string NAZN; // ����� ����������
    std::string OTPR; // ����� �����������
};

int lab4_3() {
    const int numTrains = 6;
    TRAIN RASP[numTrains];

    // ���� ������ � �������
    for (int i = 0; i < numTrains; ++i) {
        std::cout << "������� ���������� � ������ #" << i + 1 << ":\n";
        std::cout << "����� ������: ";
        std::cin >> RASP[i].NUMR;
        std::cin.ignore(); // ���������� ������ ����� ������ ����� ������

        std::cout << "����� ����������� (��:��): ";
        std::getline(std::cin, RASP[i].TIME);

        std::cout << "����� ����������: ";
        std::getline(std::cin, RASP[i].NAZN);

        std::cout << "����� �����������: ";
        std::getline(std::cin, RASP[i].OTPR);
    }

    std::string searchDestination;
    std::cout << "\n������� ����� ���������� ��� ������ �������: ";
    std::getline(std::cin, searchDestination);

    bool found = false;
    // ����� ������� � ��������� ������� ����������
    for (int i = 0; i < numTrains; ++i) {
        if (RASP[i].NAZN == searchDestination) {
            found = true;
            std::cout << "\n������ �����:\n";
            std::cout << "����� ������: " << RASP[i].NUMR << "\n";
            std::cout << "����� �����������: " << RASP[i].TIME << "\n";
            std::cout << "����� �����������: " << RASP[i].OTPR << "\n";
        }
    }

    if (!found) {
        std::cout << "������� � ����� ���������� '" << searchDestination << "' �� �������.\n";
    }

    return 0;
}