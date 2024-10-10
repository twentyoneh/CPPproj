#include <iostream>
#include <iomanip>
#include <cmath>

const int N = 4;  // Задаем размерность матрицы (4 <= n <= 16)

// Функция заполнения матрицы возрастающей последовательностью по заданной схеме
void fillMatrix(int matrix[N][N]) {
    int value = 1;
    for (int col = 0; col < N; col++) {
        if (col % 2 == 0) {
            // Заполняем столбец снизу вверх
            for (int row = 0; row < N; row++) {
                matrix[row][col] = value++;
            }
        }
        else {
            // Заполняем столбец сверху вниз
            for (int row = N - 1; row >= 0; row--) {
                matrix[row][col] = value++;
            }
        }
    }
}

// Функция для вывода матрицы на экран
void printMatrix(const double matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << std::setw(5) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Функция для нахождения детерминанта
double determinant(double matrix[N][N], int n) {
    double det = 0;
    if (n == 1) {
        return matrix[0][0];
    }

    double temp[N][N];
    int sign = 1;

    for (int f = 0; f < n; f++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == f) {
                    continue;
                }
                temp[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        det += sign * matrix[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }

    return det;
}

// Функция для нахождения обратной матрицы
bool inverseMatrix(double matrix[N][N], double inverse[N][N]) {
    double det = determinant(matrix, N);
    if (det == 0) {
        std::cout << "Матрица необратима!" << std::endl;
        return false;
    }

    double temp[N][N];
    int sign = 1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int subi = 0;
            for (int si = 0; si < N; si++) {
                if (si == i) {
                    continue;
                }
                int subj = 0;
                for (int sj = 0; sj < N; sj++) {
                    if (sj == j) {
                        continue;
                    }
                    temp[subi][subj] = matrix[si][sj];
                    subj++;
                }
                subi++;
            }
            inverse[j][i] = sign * determinant(temp, N - 1) / det;
            sign = -sign;
        }
    }
    return true;
}

// Функция для перемножения двух матриц
void multiplyMatrices(double A[N][N], double B[N][N], double result[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Главная функция программы
int lab3() {
    int matrix[N][N];            // Исходная матрица
    double inverse[N][N];        // Обратная матрица
    double matrixDouble[N][N];   // Для работы с вещественными числами (исходная матрица)
    double result[N][N];         // Результат умножения исходной матрицы на обратную

    // Заполнение матрицы
    fillMatrix(matrix);

    // Перевод целочисленной матрицы в вещественный формат
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrixDouble[i][j] = static_cast<double>(matrix[i][j]);
        }
    }

    // Вывод исходной матрицы
    std::cout << "Исходная матрица:" << std::endl;
    printMatrix(matrixDouble);

    // Нахождение обратной матрицы
    if (inverseMatrix(matrixDouble, inverse)) {
        std::cout << "Обратная матрица:" << std::endl;
        printMatrix(inverse);

        // Умножение исходной матрицы на обратную
        multiplyMatrices(matrixDouble, inverse, result);

        // Вывод результата умножения
        std::cout << "Результат умножения исходной матрицы на обратную (должна быть единичной матрицей):" << std::endl;
        printMatrix(result);
    }

    return 0;
}
