#include<iostream>

void lab2_1() {
    int N;

    // 1. Ввод массива с клавиатуры
    std::cout << "Введите количество элементов массива: ";
    std::cin >> N;

    // Выделение памяти для массива
    double* arr = new double[N];

    std::cout << "Введите " << N << " вещественных чисел: " << std::endl;
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 50 - 50;
    }

    // 2. Поиск максимального элемента
    double max_element = arr[0];
    for (int i = 1; i < N; i++) {
        if (arr[i] > max_element) {
            max_element = arr[i];
        }
    }
    std::cout << "Максимальный элемент: " << max_element << std::endl;

    // 3. Вычисление среднего арифметического положительных элементов
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
        std::cout << "Среднее арифметическое положительных элементов: " << average_positive << std::endl;
    }
    else {
        std::cout << "В массиве нет положительных элементов." << std::endl;
    }

    // 4. Вывод отрицательных элементов в обратном порядке
    std::cout << "Отрицательные элементы в обратном порядке: ";
    for (int i = N - 1; i >= 0; i--) {
        if (arr[i] < 0) {
            std::cout << arr[i] << " ";
        }
    }
    std::cout << std::endl;

    // Освобождение памяти
    delete[] arr;

}

void lab2_2() {
    const int rows = 5;
    const int cols = 4;
    int matrix[rows][cols];

    // Ввод матрицы
    std::cout << "Введите элементы матрицы 5x4: " << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> matrix[i][j];
        }
    }

    // Поиск строки с первым нулевым элементом
    int zero_row_index = -1;  // Индекс строки с первым нулем
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                zero_row_index = i;
                break;  // Прерываем внутренний цикл
            }
        }
        if (zero_row_index != -1) {
            break;  // Прерываем внешний цикл
        }
    }

    // Если нашли строку с нулевым элементом, меняем её с первой строкой
    if (zero_row_index != -1) {
        for (int j = 0; j < cols; j++) {
            std::swap(matrix[0][j], matrix[zero_row_index][j]);
        }

        std::cout << "Первая строка и строка с первым нулевым элементом поменяны местами." << std::endl;
    }
    else {
        std::cout << "В матрице нет нулевых элементов." << std::endl;
    }

    // Вывод изменённой матрицы
    std::cout << "Изменённая матрица: " << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void lab2_3() {
    int N;

    // Ввод массива
    std::cout << "Введите количество элементов массива: ";
    std::cin >> N;

    int* arr = new int[N];  // Динамическое выделение памяти для массива

    std::cout << "Введите " << N << " целых чисел: " << std::endl;
    for (int i = 0; i < N; i++) {
        std::cin >> arr[i];
    }

    // Сортировка методом прямого включения
    for (int i = 1; i < N; i++) {
        int key = arr[i];
        int j = i - 1;

        // Перемещаем элементы arr[0..i-1], которые больше key, на одну позицию вправо
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Вставляем текущий элемент в нужное место
        arr[j + 1] = key;
    }

    // Вывод отсортированного массива
    std::cout << "Отсортированный массив: ";
    for (int i = 0; i < N; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Освобождение памяти
    delete[] arr;
}

void lab2() {
    int choise;
    std::cout << "Введите номер лабы(1-3): ";
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
        std::cout << "Вы введи неверный номер лабы! ";
        break;
    }
}