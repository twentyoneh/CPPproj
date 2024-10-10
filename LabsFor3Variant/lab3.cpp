#include <iostream>
#include <iomanip>
#include <cmath>

const int N = 4;  // ������ ����������� ������� (4 <= n <= 16)

// ������� ���������� ������� ������������ ������������������� �� �������� �����
void fillMatrix(int matrix[N][N]) {
    int value = 1;
    for (int col = 0; col < N; col++) {
        if (col % 2 == 0) {
            // ��������� ������� ����� �����
            for (int row = 0; row < N; row++) {
                matrix[row][col] = value++;
            }
        }
        else {
            // ��������� ������� ������ ����
            for (int row = N - 1; row >= 0; row--) {
                matrix[row][col] = value++;
            }
        }
    }
}

// ������� ��� ������ ������� �� �����
void printMatrix(const double matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << std::setw(5) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// ������� ��� ���������� ������������
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

// ������� ��� ���������� �������� �������
bool inverseMatrix(double matrix[N][N], double inverse[N][N]) {
    double det = determinant(matrix, N);
    if (det == 0) {
        std::cout << "������� ����������!" << std::endl;
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

// ������� ��� ������������ ���� ������
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

// ������� ������� ���������
int lab3() {
    int matrix[N][N];            // �������� �������
    double inverse[N][N];        // �������� �������
    double matrixDouble[N][N];   // ��� ������ � ������������� ������� (�������� �������)
    double result[N][N];         // ��������� ��������� �������� ������� �� ��������

    // ���������� �������
    fillMatrix(matrix);

    // ������� ������������� ������� � ������������ ������
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrixDouble[i][j] = static_cast<double>(matrix[i][j]);
        }
    }

    // ����� �������� �������
    std::cout << "�������� �������:" << std::endl;
    printMatrix(matrixDouble);

    // ���������� �������� �������
    if (inverseMatrix(matrixDouble, inverse)) {
        std::cout << "�������� �������:" << std::endl;
        printMatrix(inverse);

        // ��������� �������� ������� �� ��������
        multiplyMatrices(matrixDouble, inverse, result);

        // ����� ���������� ���������
        std::cout << "��������� ��������� �������� ������� �� �������� (������ ���� ��������� ��������):" << std::endl;
        printMatrix(result);
    }

    return 0;
}
