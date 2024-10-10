
#include<iostream>
using namespace std;

const double epsilon = 0.001;

double  calculate_series(double x) {
    double term = x;       // ������ ���� ����
    double sum = term;     // ��������� ����� ����
    int n = 1;             // ������ ����� ����

    while (std::abs(term) > epsilon) {
        n++;  // ����������� ������

        // ������������ ��������� ���� ���� �� ������� (-1)^(n-1) * (x^(2n-1)) / (2n-1)
        term *= (-1) * x * x;  // x^(2n-1) = ���������� ���� �������� �� x^2, (-1) ��� ����������� ������
        term /= (2 * n - 1);   // ����� �� (2n-1)

        sum += term;           // ��������� ���� ���� � �����
    }

    return sum;
}


int fact(int num) {
    int res = 1;
    for (int i = 1; i <= num; i++)
    {
        res *= i;
    }
    return res;
}

bool is_odd_and_tripled(int number) {
    return (number % 3 == 0) && ((number / 3) % 2 != 0);
}
// 1_1
void  lab1_1() {

    double pi = 3.1415926535;
    double a, b;
    double res;
    cout << "������� �:";
    cin >> a;
    cout << "������� b:";
    cin >> b;
    res = atan(sin(a + pi) / cos(b + 2.87)) / sqrt(a + pow(cos(b), 2));
    cout << "�������� ������: %f", res;
}



void  lab1_2() {
    double x1 = 0.1;
    double x2 = 0.9;
    double x3 = -0.62;

    cout << "F(x1) = " << calculate_series(x1) << std::endl;
    cout << "F(x2) = " << calculate_series(x2) << std::endl;
    cout << "F(x3) = " << calculate_series(x3) << std::endl;
}

//1_3
void  lab1_3_1() {
    int n, j = 1;
    cout << "������� n: ";
    cin >> n;
    while (j <= n) {
        if (n % j == 0) {
            cout << j << "; ";
        }
        j++;
    }
}

void  lab1_3_2() {
    const int size = 100;
    double numbers[size];
    double max_val = std::numeric_limits<double>::lowest();  // ������������� ����������� ��������� ���������
    double min_val = std::numeric_limits<double>::max();     // ������������� ������������ ��������� ���������

    // ���� 100 ������������ �����
    std::cout << "Enter 100 real numbers: " << std::endl;
    for (int i = 0; i < size; i++) {
        std::cin >> numbers[i];

        // ������� ������������ � ����������� ��������
        if (numbers[i] > max_val) {
            max_val = numbers[i];
        }
        if (numbers[i] < min_val) {
            min_val = numbers[i];
        }
    }

    // ��������� ��������
    double difference = max_val - min_val;

    // ������� ���������
    std::cout << "������������ ��������: " << max_val << std::endl;
    std::cout << "����������� ��������: " << min_val << std::endl;
    std::cout << "������� ���� max � min: " << difference << std::endl;
}

void lab1_3_3() {
    int n;
    long long res = 1;
    cout << "������e n: ";
    cin >> n;
    if (n % 2 == 0) {
        for (int i = 1; i <= n; i += 2)
        {
            res *= i;
        }
    }
    else
    {
        for (int i = 1; i <= n; i += 1)
        {
            res *= i;
        }
    }
    cout << "���������: " << res;
}

void lab1_3_4() {
    int k, x, m, n;
    float res = 0;
    cout << "������e n: ";
    cin >> n;
    cout << "������e x: ";
    cin >> x;
    for (int k = 1; k < n; k++)
    {
        for (int m = 1; m < n; m++)
        {
            res += (x + k) / m;
        }
    }
    cout << "���������: " << res;
}

void lab1_3_5() {
    int i, j, n;
    float res = 0;
    cout << "������e n: ";
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            res += 1 / i+j;
        }
    }
    cout << "���������: " << res;
}



void lab1_3_6() {
    double tmp = 0, res = 0;
    for (int k = 1; k  < 10; k++)
    {
        for (int n = 1; n  < k; n++)
        {
            tmp = sin(k * n);
        }
        res += tmp / fact(k);
    }
    cout << "���������: " << res;
}

void lab1_3_7() {
    int n;
    int sum = 0;

    cout << "������� n";
    std::cin >> n;

    // ���� �� ��������� i �� 1 �� n
    for (int i = 1; i <= n; i++) {
        // ���������� ����� �� ������� (i^3) - 3 * i * (n^2) + n
        int result = (i * i * i) - 3 * i * (n * n) + n;

        // ��������, �������� �� ��������� ��������� �������� ������
        if (is_odd_and_tripled(result)) {
            sum += result;  // ��������� � �����, ���� ������� ���������
        }
    }

    std::cout << "���������: " << sum << std::endl;

}

void lab1_4() {
    int n;
    cout << "������� n";
    cin >> n;
    if (n >= 5 && n <= 0) {
        cout << "����� ������ � ������� �� 0 �� 5";
    }
    else
    {
        cout << "����� �� ������ � ������� �� 0 �� 5";
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int choice;
    std::cout << "������� ����� ����(1-10): ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        lab1_1();
        break;
    case 2:
        lab1_2();
        break;
    case 3:
        lab1_3_1();
        break;
    case 4:
        lab1_3_2();
        break;
    case 5:
        lab1_3_3();
        break;
    case 6:
        lab1_3_4();
        break;
    case 7:
        lab1_3_5();
        break;
    case 8:
        lab1_3_6();
        break;
    case 9:
        lab1_3_7();
        break;
    case 10:
        lab1_4();
        break;
    default:
        std::cout << "������� ����� �����!" << std::endl;
    }
    return 0;
}