#include<iostream>

void lab2_1() {
    int N;

    // 1. ���� ������� � ����������
    std::cout << "������� ���������� ��������� �������: ";
    std::cin >> N;

    // ��������� ������ ��� �������
    double* arr = new double[N];

    std::cout << "������� " << N << " ������������ �����: " << std::endl;
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 50 - 50;
    }

    // 2. ����� ������������� ��������
    double max_element = arr[0];
    for (int i = 1; i < N; i++) {
        if (arr[i] > max_element) {
            max_element = arr[i];
        }
    }
    std::cout << "������������ �������: " << max_element << std::endl;

    // 3. ���������� �������� ��������������� ������������� ���������
    double sum_positive = 0.0;
    int count_positive = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i] > 0) {
            sum_positive += arr[i];
            count_positive++;
        }
    }

    if (count_positive > 0) {
        double average_positive = sum_positive / count_positive;
        std::cout << "������� �������������� ������������� ���������: " << average_positive << std::endl;
    }
    else {
        std::cout << "� ������� ��� ������������� ���������." << std::endl;
    }

    // 4. ����� ������������� ��������� � �������� �������
    std::cout << "������������� �������� � �������� �������: ";
    for (int i = N - 1; i >= 0; i--) {
        if (arr[i] < 0) {
            std::cout << arr[i] << " ";
        }
    }
    std::cout << std::endl;

    // ������������ ������
    delete[] arr;

}

void lab2_2() {
    const int rows = 5;
    const int cols = 4;
    int matrix[rows][cols];

    // ���� �������
    std::cout << "������� �������� ������� 5x4: " << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> matrix[i][j];
        }
    }

    // ����� ������ � ������ ������� ���������
    int zero_row_index = -1;  // ������ ������ � ������ �����
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                zero_row_index = i;
                break;  // ��������� ���������� ����
            }
        }
        if (zero_row_index != -1) {
            break;  // ��������� ������� ����
        }
    }

    // ���� ����� ������ � ������� ���������, ������ � � ������ �������
    if (zero_row_index != -1) {
        for (int j = 0; j < cols; j++) {
            std::swap(matrix[0][j], matrix[zero_row_index][j]);
        }

        std::cout << "������ ������ � ������ � ������ ������� ��������� �������� �������." << std::endl;
    }
    else {
        std::cout << "� ������� ��� ������� ���������." << std::endl;
    }

    // ����� ��������� �������
    std::cout << "��������� �������: " << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void lab2_3() {
    int N;

    // ���� �������
    std::cout << "������� ���������� ��������� �������: ";
    std::cin >> N;

    int* arr = new int[N];  // ������������ ��������� ������ ��� �������

    std::cout << "������� " << N << " ����� �����: " << std::endl;
    for (int i = 0; i < N; i++) {
        std::cin >> arr[i];
    }

    // ���������� ������� ������� ���������
    for (int i = 1; i < N; i++) {
        int key = arr[i];
        int j = i - 1;

        // ���������� �������� arr[0..i-1], ������� ������ key, �� ���� ������� ������
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // ��������� ������� ������� � ������ �����
        arr[j + 1] = key;
    }

    // ����� ���������������� �������
    std::cout << "��������������� ������: ";
    for (int i = 0; i < N; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // ������������ ������
    delete[] arr;
}

void lab2() {
    int choise;
    std::cout << "������� ����� ����(1-3): ";
    std::cin >> choise;
    switch (choise)
    {
    case 1:
        lab2_1();
        break;
    case 2:
        lab2_2();
        break;
    case 3:
        lab2_3();
        break;
    default:
        std::cout << "�� ����� �������� ����� ����! ";
        break;
    }
}